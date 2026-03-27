/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseFactory.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 10:07:42 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/27 12:48:24 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ResponseFactory.hpp"
#include "AutoIndexResponse.hpp"
#include "ErrorResponse.hpp"
#include "StaticResponse.hpp"

namespace http
{
    ResponseFactory::ResponseFactory() {}

    ResponseFactory::~ResponseFactory() {}

    http::IResponse *ResponseFactory::createAutoIndexResponse(core::Server &server, http::Request &request)
    {
        return (new AutoIndexResponse(server, request));
    }

    http::IResponse *ResponseFactory::createErrorResponse(core::Server &server, http::Request &request, http::StatusCode statusCode)
    {
        return (new ErrorResponse(server, request, statusCode));
    }

    http::IResponse *ResponseFactory::createStaticResponse(core::Server &server, http::Request &request, std::size_t bodySize)
    {
        return (new StaticResponse(server, request, bodySize));
    }
}