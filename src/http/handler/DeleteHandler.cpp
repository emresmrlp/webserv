/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 17:02:19 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/29 01:41:10 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DeleteHandler.hpp"
#include <cstdio>
#include <string>
#include "ConfigLocation.hpp"
#include "Request.hpp"
#include "ResponseFactory.hpp"
#include "StatusCode.hpp"
#include "Util.hpp"

namespace http
{
	DeleteHandler::DeleteHandler(ResponseFactory &factory) : _factory(factory) {}

	DeleteHandler::~DeleteHandler() {}

	http::IResponse *DeleteHandler::handle(const config::ConfigServer *config, const config::ConfigLocation *configLoc,
		http::Request *request) const
	{
		std::string		fileName;

		if (configLoc->getUploadPath().empty())
			fileName = util::getRelativeConfigPath(config, configLoc) + request->getPath();
		else
			fileName = configLoc->getUploadPath() + request->getPath();
		
		if (std::remove(fileName.c_str()) == 0)
			return (this->_factory.createSuccessResponse(config, request, http::NO_CONTENT));
		return (this->_factory.createStatusResponse(config, request, http::NOT_FOUND));
	}
}