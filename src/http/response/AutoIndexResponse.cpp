/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AutoIndexResponse.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:26 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/05 17:08:48 by ysumeral         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "AutoIndexResponse.hpp"
#include "StatusCode.hpp"
#include <iostream>
#include "Request.hpp"
#include <iomanip>
#include <sstream>
#include <dirent.h>
#include <map>

namespace http
{
    AutoIndexResponse::AutoIndexResponse(const config::ConfigServer &config, const Request *request)
        : AResponseBase(config, request)
    {
        this->createDefaultBody();
        this->initHeaders();
        this->addHeader("Content-Type", "text/html");
    }

    AutoIndexResponse::~AutoIndexResponse() {}

    void AutoIndexResponse::initHeaders()
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

    void    AutoIndexResponse::createDefaultBody()
    {
        std::stringstream   body_oss;
        std::string         fileName;
        DIR* dir;

        body_oss << "<!DOCTYPE html><html><head><title>Webserv - Index of " << this->_request->getPath() << "</title></head>"    
            << "<body style='font-size: 24px;'><h1>" << "Webserv - Index of " << this->_request->getPath() << "</h1>"
            << "<hr>"
            << "<a href='../' style='display: block;'>../</a>\n";
        dir = opendir((this->_config.getRoot() + "/" + this->_request->getPath()).c_str());
        if (dir != NULL)
        {
            struct dirent *ent;

            while ((ent = readdir(dir)) != NULL)
            {
                fileName = ent->d_name;
                if (fileName != "." && fileName != "..")
                    body_oss << "<a href='" << fileName << "' style='display: block;'>" << fileName << "</a>\n";
            }
            closedir(dir);
        }
        
        body_oss << "<hr></body></html>";
        this->setBody(body_oss.str());
    }

    std::string AutoIndexResponse::serialize() const
    {
		std::ostringstream response;
		
		response << this->buildHeader();
		response << this->_body;
		return (response.str());
    }
}