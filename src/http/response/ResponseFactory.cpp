/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseFactory.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 10:07:42 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/22 14:23:05 by ysumeral         ###   ########.fr       */
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

    http::IResponse *ResponseFactory::createAutoIndexResponse(const std::string &directory)
    {
        (void)directory;
        return (new AutoIndexResponse());
    }

    http::IResponse *ResponseFactory::createErrorResponse(http::StatusCode statusCode)
    {
        return (new ErrorResponse(statusCode));
    }

    http::IResponse *ResponseFactory::createStaticResponse(const http::Request &request, std::size_t bodySize)
    {
        return (new StaticResponse(request, bodySize));
    }
}