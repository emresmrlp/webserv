/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PutHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 17:03:06 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/29 01:36:05 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PutHandler.hpp"
#include <fstream>
#include <string>
#include "ConfigLocation.hpp"
#include "Request.hpp"
#include "ResponseFactory.hpp"
#include "StatusCode.hpp"
#include "Util.hpp"

namespace http
{
	PutHandler::PutHandler(ResponseFactory &factory) : _factory(factory) {}

	PutHandler::~PutHandler() {}

	http::IResponse *PutHandler::handle(const config::ConfigServer *config, const config::ConfigLocation *configLoc,
		http::Request *request) const
	{
		if (configLoc->getUploadPath().empty())
			return (this->_factory.createStatusResponse(config, request, http::FORBIDDEN));
			
		std::string		fileName = configLoc->getUploadPath() + request->getPath();
		bool			isFileExist = util::isFileExist(fileName);

		if (util::isDirExist(fileName))
			return (this->_factory.createStatusResponse(config, request, http::FORBIDDEN));
		if (request->getBody().size() > configLoc->getMaxBodySize())
			return (this->_factory.createStatusResponse(config, request, http::PAYLOAD_TOO_LARGE));

		std::ofstream	file(fileName.c_str(), std::ios::binary);
		if (!file.is_open())
			return (this->_factory.createStatusResponse(config, request, http::INTERNAL_SERVER_ERROR));

		file.write(request->getBody().c_str(), request->getBody().size());
		if (file.fail())
			return (this->_factory.createStatusResponse(config, request, http::INTERNAL_SERVER_ERROR));

		file.close();
		if (isFileExist)
			return (this->_factory.createSuccessResponse(config, request, http::OK));
		return (this->_factory.createSuccessResponse(config, request, http::CREATED));
	}
}