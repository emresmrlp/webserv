/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedirectResponse.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:26 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/13 09:04:21 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RedirectResponse.hpp"
#include <vector>
#include <iostream>
#include <sys/stat.h>

namespace http
{
	RedirectResponse::RedirectResponse(const config::ConfigServer &config, std::pair<int, std::string> redirectPair)
		: AResponseBase(config, NULL)
	{
		this->_statusCode = static_cast<http::StatusCode>(redirectPair.first);
		this->_statusMessage = this->getStatusMessage(this->_statusCode);
		this->setBody("");
		this->addHeader("Date", http::AResponseBase::getDate());
        this->addHeader("Server", this->_config.getSignature());
        this->addHeader("Location", redirectPair.second);
		this->addHeader("Content-Type", "text/html");
        std::ostringstream oss;
        oss << this->_body.length();
		this->addHeader("Content-Length", oss.str());
		this->addHeader("Connection", "close");
	}

	RedirectResponse::~RedirectResponse() {}

	std::string RedirectResponse::serialize() const
	{
		std::ostringstream response;
		
		response << this->buildHeader();
		if (this->_request->getMethod() != "HEAD")
			response << this->_body;
		return (response.str());
	}
}