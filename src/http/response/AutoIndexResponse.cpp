/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AutoIndexResponse.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:26 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/27 11:39:08 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AutoIndexResponse.hpp"
#include <iostream>

namespace http
{
	AutoIndexResponse::AutoIndexResponse(core::Server server, http::Request request) : AResponseBase(server, request)
	{
		this->_statusCode = OK;
		this->_statusMessage = this->getStatusMessage(this->_statusCode);
		this->createBody();
		this->addHeader("Date", http::AResponseBase::getDate());
        this->addHeader("Server", this->_signature);
		//TODO where is the host
		this->addHeader("Content-Type", "text/html");
        std::ostringstream oss;
        oss << this->_body.length();
		this->addHeader("Content-Length", oss.str());
		this->addHeader("Connection", "close");
	}

	AutoIndexResponse::~AutoIndexResponse() {}

	std::string AutoIndexResponse::serialize() const
	{
		std::ostringstream response;
		
		response << this->buildHeader();
		response << this->_body;
		return (response.str());
	}

	void AutoIndexResponse::createBody()
	{
		std::stringstream body_oss;
		
		body_oss << "<!DOCTYPE html><html><body><h2>AUTOINDEX PAGE -> INDEX.HTML TIKLAYINIZ.</h2><h1><a href=\"index.html\">INDEX.HTML</a></h1></body></html>";
		this->setBody(body_oss.str());
	}
}