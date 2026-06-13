/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OkResponse.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:26 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/13 09:04:08 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OkResponse.hpp"
#include "StatusCode.hpp"
#include <iostream>
#include "Request.hpp"
#include <iomanip>
#include <sstream>

#include <map>

namespace http
{
    OkResponse::OkResponse(const config::ConfigServer &config, const Request *request)
        : AResponseBase(config, request)
    {
        this->createBody();
        this->initHeaders();
        this->addHeader("Content-Type", this->getMimeType(this->_request->getPath()));
    }

    OkResponse::OkResponse(const config::ConfigServer &config, const Request *request, const std::string &path)
        : AResponseBase(config, request)
    {
        this->createBody(path);
        this->initHeaders();
        this->addHeader("Content-Type", "text/html");
    }

    OkResponse::~OkResponse() {}

    void OkResponse::initHeaders()
    {
        std::ostringstream oss;
        
        this->_statusCode = OK;
        this->_statusMessage = this->getStatusMessage(this->_statusCode);
        this->addHeader("Date", http::AResponseBase::getDate());
        this->addHeader("Server", this->_signature);
        oss << this->_body.size();
		this->addHeader("Content-Length", oss.str());
		this->addHeader("Connection", "close");
    }

    std::string OkResponse::serialize() const
    {
		std::ostringstream response;
		
		response << this->buildHeader();
        if (this->_request->getMethod() != "HEAD")
		    response << this->_body;
		return (response.str());
    }
}