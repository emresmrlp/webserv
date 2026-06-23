/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StatusResponse.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:26 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/13 10:53:00 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StatusResponse.hpp"
#include "Util.hpp"
#include <vector>
#include <iostream>
#include <sys/stat.h>

namespace http
{
	StatusResponse::StatusResponse(const config::ConfigServer &config, const Request *request, StatusCode status)
		: AResponseBase(config, request)
	{
		this->_statusCode = status;

		std::string errorPage = this->_config.getRoot() + "/" + this->_config.getErrorPage(static_cast<int>(status));

		std::cout << "! DEBUG: errorpage: " << errorPage << std::endl;

		if (util::isFileExist(errorPage))
			this->createBody(errorPage);
		else
			this->createDefaultBody();
		
		if (this->_statusCode == METHOD_NOT_ALLOWED)
		{
			std::ostringstream result;
			if (!this->_request->getPath().empty())
			{
				std::vector<std::string>::const_iterator it
					= this->_config.getLocation(this->_request->getPath())->getAllowedMethods().begin();
				std::vector<std::string>::const_iterator itEnd
					= this->_config.getLocation(this->_request->getPath())->getAllowedMethods().end();
				while (it != itEnd)
				{
					if (!result.str().empty())
						result << ", ";
					result << *it;
					++it;
				}
				this->addHeader("Allow", result.str());
			}
		}
		this->addHeader("Content-Type", "text/html");
		this->addHeader("Content-Length", util::toString(this->_body.size()));
	}

	StatusResponse::~StatusResponse() {}

	void StatusResponse::createDefaultBody()
	{
		std::stringstream body_oss;
	
		body_oss << "<!DOCTYPE html><html>"
				<< "<title>" << this->_statusCode << " - " << this->getStatusMessage(this->_statusCode) << "</title>"
				<< "<body><h1>WEBSERV</h1>"
				<< "<h2>" << this->_statusCode << " - " << this->getStatusMessage(this->_statusCode) << "</h2>"
				<< "Developed by <b>ysumeral, beldemir (C) 2026</b></div>"
			<< "</body></html>";

		this->setBody(body_oss.str());
	}
}