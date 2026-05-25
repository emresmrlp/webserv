/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseDispatcher.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:26 by ysumeral          #+#    #+#             */
/*   Updated: 2026/05/25 16:21:22 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ResponseDispatcher.hpp"
#include "StatusCode.hpp"
#include "Request.hpp"
#include "Server.hpp"
#include <sys/stat.h>
#include <string>

namespace http
{
    ResponseDispatcher::ResponseDispatcher(const config::ConfigServer &config,  ResponseFactory &factory)
        : _config(config), _factory(factory) {}

    ResponseDispatcher::~ResponseDispatcher() {}

    http::IResponse *ResponseDispatcher::dispatch(http::Request &request)
    {
        http::IResponse *response;
        struct stat st;

        std::string filePath = this->_config.getRoot(); // TODO
        filePath += request.getPath();
        response = this->_factory.createErrorResponse(this->_config, request.getPath(), http::FORBIDDEN);
        if (stat(filePath.c_str(), &st) != 0)
        {
            std::cout << "404 File not found: " << request.getPath() << std::endl;
            response = this->_factory.createErrorResponse(this->_config, request.getPath(), http::NOT_FOUND);
        }
        else if (S_ISREG(st.st_mode))
            response = this->_factory.createStaticResponse(this->_config, &request, st.st_size);
        else if (S_ISDIR(st.st_mode))
        {
            if (this->_config.getLocations()[0].getAutoIndex()) //(request.getPath()).getAutoIndex())
                response = this->_factory.createAutoIndexResponse(this->_config, &request);
            else
                response = this->_factory.createErrorResponse(this->_config, request.getPath(), http::FORBIDDEN);
        }
        return (response);
    }
}