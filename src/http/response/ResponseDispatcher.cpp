/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseDispatcher.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:26 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/29 01:48:00 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ResponseDispatcher.hpp"
#include <utility>
#include "Util.hpp"
#include "CGIHandler.hpp"
#include "ConfigLocation.hpp"
#include "ConfigServer.hpp"
#include "DeleteHandler.hpp"
#include "GetHandler.hpp"
#include "HeadHandler.hpp"
#include "IMethodHandler.hpp"
#include "PostHandler.hpp"
#include "PutHandler.hpp"
#include "Request.hpp"
#include "ResponseFactory.hpp"
#include "StatusCode.hpp"

namespace http
{
	class IResponse;
	
	ResponseDispatcher::ResponseDispatcher(ResponseFactory &factory)
		: _factory(factory)
	{
		this->_handlers["GET"] = new GetHandler(this->_factory);
		this->_handlers["HEAD"] = new HeadHandler(this->_factory);
		this->_handlers["POST"] = new PostHandler(this->_factory);
		this->_handlers["PUT"] = new PutHandler(this->_factory);
		this->_handlers["DELETE"] = new DeleteHandler(this->_factory);
		this->_handlers["CGI"] = new CGIHandler(this->_factory);
	}

	ResponseDispatcher::~ResponseDispatcher()
	{
		std::map<std::string, IMethodHandler*>::iterator it;

		for (it = _handlers.begin(); it != _handlers.end(); ++it)
			delete (it->second);
	}

	http::IResponse *ResponseDispatcher::dispatch(const config::ConfigServer *config, http::Request *request)
	{
		const config::ConfigLocation *configLoc;

		configLoc = config->getLocation(request->getPath());
		if (configLoc->hasRedirection())
		{
			std::pair<int, std::string> redirectPair;

			redirectPair = configLoc->getReturnRedirection();
			if (redirectPair.second == request->getPath())
				return (this->_factory.createStatusResponse(config, request, http::INTERNAL_SERVER_ERROR));
			return (this->_factory.createRedirectResponse(config, redirectPair));
		}

		ParsedURI URI = CGIHandler::parseURI(util::getRelativeConfigPath(config, configLoc) + request->getPath());

		bool isCgi = false;
		if (!configLoc->getCgiPass(util::getExtension(URI.scriptPath)).empty())
			isCgi = true;

		std::map<std::string, http::IMethodHandler *>::iterator it;
		it = this->_handlers.find(request->getMethod());
		if (it == this->_handlers.end())
			return (this->_factory.createStatusResponse(config, request, http::NOT_IMPLEMENTED));

		if (isCgi)
			return (this->_handlers.find("CGI")->second->handle(config, configLoc, request));

		if (!configLoc->isAllowed(request->getMethod()))
			return (this->_factory.createStatusResponse(config, request, http::METHOD_NOT_ALLOWED));

		return (it->second->handle(config, configLoc, request));
	}
}