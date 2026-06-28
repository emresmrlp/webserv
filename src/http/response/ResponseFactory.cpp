/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseFactory.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 10:07:42 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/29 01:53:35 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ResponseFactory.hpp"
#include "AutoIndexResponse.hpp"
#include "CGIResponse.hpp"
#include "RedirectResponse.hpp"
#include "StatusResponse.hpp"
#include "SuccessResponse.hpp"

namespace config
{
	class ConfigServer;
}

namespace http
{
	ResponseFactory::ResponseFactory() {}

	ResponseFactory::~ResponseFactory() {}

	http::IResponse *ResponseFactory::createStatusResponse(const config::ConfigServer *config, http::Request *request, http::StatusCode statusCode)
	{
		return (new StatusResponse(*config, request, statusCode));
	}

	http::IResponse *ResponseFactory::createRedirectResponse(const config::ConfigServer *config, std::pair<int, std::string> redirectPair)
	{
		return (new RedirectResponse(*config, redirectPair));
	}

	http::IResponse *ResponseFactory::createSuccessResponse(const config::ConfigServer *config, http::Request *request, http::StatusCode status)
	{
		return (new SuccessResponse(*config, request, status));
	}

	http::IResponse *ResponseFactory::createSuccessResponseWithPath(const config::ConfigServer *config, http::Request *request, const std::string &path)
	{
		return (new SuccessResponse(*config, request, path));
	}

	http::IResponse *ResponseFactory::createAutoIndexResponse(const config::ConfigServer *config, http::Request *request)
	{
		return (new AutoIndexResponse(*config, request));
	}
	http::IResponse *ResponseFactory::createCGIResponse(const config::ConfigServer *config, http::Request *request, const std::string &path)
	{
		return (new CGIResponse(*config, request, path));
	}
}