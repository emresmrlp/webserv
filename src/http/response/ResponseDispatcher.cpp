/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseDispatcher.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:26 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/22 18:21:07 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ResponseDispatcher.hpp"
#include "Config.hpp"
#include "StatusCode.hpp"
#include "Request.hpp"
#include <sys/stat.h>
#include <string>

namespace http
{
    ResponseDispatcher::ResponseDispatcher(ResponseFactory &factory) : _factory(factory) {}

    ResponseDispatcher::~ResponseDispatcher() {}

    http::IResponse *ResponseDispatcher::dispatch(http::Request &request) // dispatcher(factory, request, conf)?
    {
        http::IResponse *response;
        struct stat st;
        
        // TODO: filePath must be fixed with ConfigLocation
        std::string filePath = ROOT; // TODO
        filePath += request.getPath(); // TODO
        response = this->_factory.createErrorResponse(http::FORBIDDEN);
        if (stat(filePath.c_str(), &st) != 0)
        {
            std::cout << "404 File not found: " << request.getPath() << std::endl;
            response = this->_factory.createErrorResponse(http::NOT_FOUND);
        }
        else if (S_ISREG(st.st_mode))
            response = this->_factory.createStaticResponse(request, st.st_size);
        else if (S_ISDIR(st.st_mode))
        {
            if (AUTOINDEX)
                response = this->_factory.createAutoIndexResponse(filePath);
            else
                response = this->_factory.createErrorResponse(FORBIDDEN);
        }
        return (response);
    }
}