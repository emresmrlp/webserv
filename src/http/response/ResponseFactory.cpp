/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseFactory.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 10:07:42 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/13 09:33:34 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ResponseFactory.hpp"
#include "ErrorResponse.hpp"
#include "OkResponse.hpp"
#include "RedirectResponse.hpp"
#include "AutoIndexResponse.hpp"

namespace http
{
	ResponseFactory::ResponseFactory() {}

	ResponseFactory::~ResponseFactory() {}

	http::IResponse *ResponseFactory::createErrorResponse(const config::ConfigServer *config, http::Request *request, http::StatusCode statusCode)
	{
		return (new ErrorResponse(*config, request, statusCode));
	}

	http::IResponse *ResponseFactory::createRedirectResponse(const config::ConfigServer *config, std::pair<int, std::string> redirectPair)
	{
		return (new RedirectResponse(*config, redirectPair));
	}

	http::IResponse *ResponseFactory::createOkResponse(const config::ConfigServer *config, http::Request *request)
	{
		return (new OkResponse(*config, request));
	}

	http::IResponse *ResponseFactory::createPathOkResponse(const config::ConfigServer *config, http::Request *request, const std::string &path)
	{
		return (new OkResponse(*config, request, path));
	}

	http::IResponse *ResponseFactory::createAutoIndexResponse(const config::ConfigServer *config, http::Request *request)
	{
		return (new AutoIndexResponse(*config, request));
	}
}