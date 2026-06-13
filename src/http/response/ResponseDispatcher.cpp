/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseDispatcher.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:26 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/13 20:21:44 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ResponseDispatcher.hpp"
#include "StatusCode.hpp"
#include "Request.hpp"
#include "Server.hpp"
#include <sys/stat.h>
#include <string>
#include <Util.hpp>
#include "GetHandler.hpp"
#include "HeadHandler.hpp"
// #include "PostHandler.hpp"
// #include "DeleteHandler.hpp"
// #include "PutHandler.hpp"

namespace http
{
	ResponseDispatcher::ResponseDispatcher(ResponseFactory &factory)
		: _factory(factory)
	{
		this->_handlers["GET"] = new GetHandler(this->_factory);
		this->_handlers["HEAD"] = new HeadHandler(this->_factory);
		// this->_handlers["POST"] = new PostHandler();
		// this->_handlers["DELETE"] = new DeleteHandler();
		// this->_handlers["PUT"] = new PutHandler();
	}

	ResponseDispatcher::~ResponseDispatcher()
	{
		std::map<std::string, IMethodHandler*>::iterator it;

		for (it = _handlers.begin(); it != _handlers.end(); ++it)
			delete (it->second);
	}

	http::IResponse *ResponseDispatcher::dispatch(const config::ConfigServer *config, http::Request *request)
	{
		const config::ConfigLocation *configLocation;

		configLocation = config->getLocation(request->getPath());
		if (configLocation->hasRedirection())
		{
			std::pair<int, std::string> redirectPair;

			redirectPair = configLocation->getReturnRedirection();
			if (redirectPair.second == request->getPath())
				return (this->_factory.createStatusResponse(config, request, http::INTERNAL_SERVER_ERROR));
			return (this->_factory.createRedirectResponse(config, redirectPair));
		}

		if (!configLocation->isAllowed(request->getMethod()))
			return (this->_factory.createStatusResponse(config, request, http::METHOD_NOT_ALLOWED));

		std::map<std::string, http::IMethodHandler *>::iterator it;
		it = this->_handlers.find(request->getMethod());
		if (it == this->_handlers.end())
			return (this->_factory.createStatusResponse(config, request, http::NOT_IMPLEMENTED));

		return (it->second->handle(config, configLocation, request));
	}
}