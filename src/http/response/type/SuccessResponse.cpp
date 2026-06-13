/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SuccessResponse.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:26 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/13 10:52:18 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuccessResponse.hpp"
#include "StatusCode.hpp"
#include <iostream>
#include "Request.hpp"
#include <iomanip>
#include <sstream>
#include "Util.hpp"
#include <map>

namespace http
{
	SuccessResponse::SuccessResponse(const config::ConfigServer &config, const Request *request, http::StatusCode statusCode)
		: AResponseBase(config, request)
	{
		this->_statusCode = statusCode;
		this->createBody();
		this->addHeader("Content-Length", util::toString(this->_body.size()));
		this->addHeader("Content-Type", this->getMimeType(this->_request->getPath()));
	}

	SuccessResponse::SuccessResponse(const config::ConfigServer &config, const Request *request, const std::string &path)
		: AResponseBase(config, request)
	{
		this->_statusCode = OK;
		this->createBody(path);
		this->addHeader("Content-Length", util::toString(this->_body.size()));
		this->addHeader("Content-Type", "text/html");
	}

	SuccessResponse::~SuccessResponse() {}
}