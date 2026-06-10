/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseDispatcher.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:26 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/10 13:50:52 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ResponseDispatcher.hpp"
#include "StatusCode.hpp"
#include "Request.hpp"
#include "Server.hpp"
#include <sys/stat.h>
#include <string>
#include <Util.hpp>

namespace http
{
	ResponseDispatcher::ResponseDispatcher(ResponseFactory &factory)
		: _factory(factory) {}

	ResponseDispatcher::~ResponseDispatcher() {}

	http::IResponse *ResponseDispatcher::dispatch(http::Request *request, const config::ConfigServer *config)
	{
		http::IResponse *response;
		struct stat st;
		const config::ConfigLocation *configLocation;

		configLocation = config->getLocation(request->getPath());
		if (configLocation->hasRedirection())
		{
			std::pair<int, std::string> redirectPair;

			redirectPair = configLocation->getReturnRedirection();
			if (redirectPair.second == request->getPath())
				response = this->_factory.createErrorResponse(config, request->getPath(), http::INTERNAL_SERVER_ERROR);
			else
				response = this->_factory.createRedirectResponse(config, redirectPair);
			return (response);
		}
		std::string filePath = config->getRoot();
		filePath += request->getPath();
		
		if (stat(filePath.c_str(), &st) != 0)
		{
			std::cout << "404 File not found: " << request->getPath() << std::endl;
			response = this->_factory.createErrorResponse(config, request->getPath(), http::NOT_FOUND);
		}
		else if (S_ISREG(st.st_mode))
			response = this->_factory.createOkResponse(config, request);
		else if (S_ISDIR(st.st_mode))
		{
			if (configLocation->getAutoIndex())
			{
				std::string indexPath;
			
				indexPath = "";
				typedef std::vector<std::string>::const_iterator IndexIt;
				for(IndexIt it = configLocation->getIndexList().begin(); it != configLocation->getIndexList().end(); it++)
				{
					indexPath = (config->getRoot() + "/" + *it);
					if (util::isFileExist(indexPath) == false)
						indexPath = "";
					if (!indexPath.empty())
						break ;
				}
				if (indexPath.empty())
					response = this->_factory.createAutoIndexResponse(config, request);
				else
					response = this->_factory.createPathOkResponse(config, request, indexPath);
			}
			else
				response = this->_factory.createErrorResponse(config, request->getPath(), http::FORBIDDEN);
		}
		else
			response = this->_factory.createErrorResponse(config, request->getPath(), http::FORBIDDEN);
		return (response);
	}
}