/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorResponse.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:26 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/13 09:43:29 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ErrorResponse.hpp"
#include "Util.hpp"
#include <vector>
#include <iostream>
#include <sys/stat.h>

namespace http
{
	ErrorResponse::ErrorResponse(const config::ConfigServer &config, const Request *request, StatusCode status)
		: AResponseBase(config, request)
	{
		this->_statusCode = status;
		this->_statusMessage = this->getStatusMessage(this->_statusCode);
		this->createDefaultBody();
		this->initHeaders();
	}

	ErrorResponse::~ErrorResponse() {}

	void ErrorResponse::initHeaders()
    {
        this->addHeader("Date", http::AResponseBase::getDate());
        this->addHeader("Server", this->_config.getSignature());
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
					result << *it;
					if (*(it + 1) != *itEnd)
						result << ", ";
					it++;
				}
				this->addHeader("Allow", result.str());
			}
		}
		this->addHeader("Content-Type", "text/html");
        std::ostringstream oss;
        oss << this->_body.length();
		this->addHeader("Content-Length", oss.str());
		this->addHeader("Connection", "close");
    }

	std::string ErrorResponse::serialize() const
	{
		std::ostringstream response;
		
		response << this->buildHeader();
		if (this->_request->getMethod() != "HEAD")
			response << this->_body;
		return (response.str());
	}

	void ErrorResponse::createDefaultBody()
	{
		std::stringstream body_oss;
	
		body_oss << "<!DOCTYPE html><html>"
				<< "<title>" << this->_statusCode << " - " << this->_statusMessage << "</title>"
				<< "<body>WEBSERV"
				<< "<h1>" << this->_statusCode << "</h1>"
				<< "<p>" << this->_statusMessage << "</p>"
				<< "Developed by <b>ysumeral, beldemir (C) 2026</b></div>"
			<< "</body></html>";

		this->setBody(body_oss.str());
	}
}