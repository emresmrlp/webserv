/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseFactory.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 10:07:42 by ysumeral          #+#    #+#             */
/*   Updated: 2026/05/31 21:00:15 by ysumeral         ###   ########.fr       */
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

    http::IResponse *ResponseFactory::createAutoIndexResponse(const config::ConfigServer *config, http::Request *request)
    {
        return (new AutoIndexResponse(*config, request));
    }

    http::IResponse *ResponseFactory::createErrorResponse(const config::ConfigServer *config, const std::string &path, http::StatusCode statusCode)
    {
        return (new ErrorResponse(*config, path, statusCode));
    }

    http::IResponse *ResponseFactory::createStaticResponse(const config::ConfigServer *config, http::Request *request, std::size_t bodySize)
    {
        return (new StaticResponse(*config, request, bodySize));
    }
}