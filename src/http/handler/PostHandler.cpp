/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PostHandler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 17:02:59 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/14 10:43:12 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PostHandler.hpp"
#include "ResponseFactory.hpp"
#include "Util.hpp"
#include <fstream>

namespace http
{
	PostHandler::PostHandler(ResponseFactory &factory) : _factory(factory) {}

	PostHandler::~PostHandler() {}

	http::IResponse *PostHandler::handle(const config::ConfigServer *config, const config::ConfigLocation *configLoc,
		http::Request *request) const
	{
		if (configLoc->getUploadPath().empty())
			return (this->_factory.createStatusResponse(config, request, http::FORBIDDEN));
		if (request->getBody().size() > config->getMaxBodySize())
			return (this->_factory.createStatusResponse(config, request, http::PAYLOAD_TOO_LARGE));

		std::string		fileName = configLoc->getUploadPath() + "/" + "upload_" + util::getCurrentTimestamp();
		std::ofstream	file(fileName, std::ios::binary);
		if (!file.is_open())
			return (this->_factory.createStatusResponse(config, request, http::INTERNAL_SERVER_ERROR));

		file.write(request->getBody().c_str(), request->getBody().size());
		if (file.fail())
			return (this->_factory.createStatusResponse(config, request, http::INTERNAL_SERVER_ERROR));

		file.close();
		return (this->_factory.createSuccessResponse(config, request, http::CREATED));
	}
}