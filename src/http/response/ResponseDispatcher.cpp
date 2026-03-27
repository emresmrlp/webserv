/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseDispatcher.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:26 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/27 12:41:48 by ysumeral         ###   ########.fr       */
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
    ResponseDispatcher::ResponseDispatcher(core::Server &server,  ResponseFactory &factory)
        : _server(server), _factory(factory) {}

    ResponseDispatcher::~ResponseDispatcher() {}

    http::IResponse *ResponseDispatcher::dispatch(http::Request &request)
    {
        http::IResponse *response;
        struct stat st;

        std::string filePath = this->_server.getConfig().getRoot(); // TODO
        filePath += request.getPath();
        response = this->_factory.createErrorResponse(this->_server, request, http::FORBIDDEN);
        if (stat(filePath.c_str(), &st) != 0)
        {
            std::cout << "404 File not found: " << request.getPath() << std::endl;
            response = this->_factory.createErrorResponse(this->_server, request, http::NOT_FOUND);
        }
        else if (S_ISREG(st.st_mode))
            response = this->_factory.createStaticResponse(this->_server, request, st.st_size);
        else if (S_ISDIR(st.st_mode))
        {
            if (this->_server.getConfig().getLocation(request.getPath()).getAutoIndex())
                response = this->_factory.createAutoIndexResponse(this->_server, request);
            else
                response = this->_factory.createErrorResponse(this->_server, request, http::FORBIDDEN);
        }
        return (response);
    }
}