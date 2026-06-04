/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticResponse.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:26 by ysumeral          #+#    #+#             */
/*   Updated: 2026/05/31 20:57:28 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StaticResponse.hpp"
#include "StatusCode.hpp"
#include <iostream>
#include "Request.hpp"
#include <iomanip>
#include <sstream>

#include <map>

namespace http
{
    StaticResponse::StaticResponse(const config::ConfigServer &config, const Request *request, std::size_t bodySize)
        : AResponseBase(config, request), _bodySize(bodySize)
    {
        this->_statusCode = OK;
        this->_statusMessage = this->getStatusMessage(this->_statusCode);
        this->createBody();
        this->addHeader("Date", http::AResponseBase::getDate());
        this->addHeader("Server", this->_signature);
		this->addHeader("Content-Type", this->getMimeType(request->getPath()));
        std::ostringstream oss;
        oss << this->_bodySize;
		this->addHeader("Content-Length", oss.str());
		this->addHeader("Connection", "close");
    }

    StaticResponse::~StaticResponse() {}

    std::string StaticResponse::serialize() const
    {
		std::ostringstream response;
		
		response << this->buildHeader();
		response << this->_body;
		return (response.str());
    }

    void StaticResponse::createBody()
    {
        std::string path;

        path = this->_config.getRoot() + this->_request->getPath();
        this->setBody(this->readFile(path));
    }
}