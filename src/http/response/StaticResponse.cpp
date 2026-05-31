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
#include <fstream>
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
		this->addHeader("Content-Type", this->getMimeType());
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

    static std::string readFile(const std::string& filePath) {
        std::ifstream file(filePath.c_str());
        if (!file.is_open())
            return "";
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        return (buffer.str());
    }

    void StaticResponse::createBody()
    {
        std::string filePath = this->_config.getRoot();
        filePath += this->_request->getPath();
        this->setBody(readFile(filePath));
    }

    const std::string StaticResponse::getMimeType() const
    {
        std::string requestPath;
        std::string contentType;

        requestPath = this->_request->getPath(); 
        std::string extension;

        extension = requestPath.substr(requestPath.find_last_of("."));
        std::map<std::string, std::string> mimeTypes;
        mimeTypes[".html"]  = "text/html";
        mimeTypes[".htm"]   = "text/html";
        mimeTypes[".css"]   = "text/css";
        mimeTypes[".js"]    = "application/javascript";
        mimeTypes[".mjs"]   = "text/javascript";
        mimeTypes[".json"]  = "application/json";
        mimeTypes[".xml"]   = "application/xml";
        mimeTypes[".txt"]   = "text/plain";
        mimeTypes[".csv"]   = "text/csv";
        mimeTypes[".md"]    = "text/markdown";
        mimeTypes[".yaml"]  = "text/yaml";
        mimeTypes[".yml"]   = "text/yaml";
        mimeTypes[".png"]   = "image/png";
        mimeTypes[".jpg"]   = "image/jpeg";
        mimeTypes[".jpeg"]  = "image/jpeg";
        mimeTypes[".gif"]   = "image/gif";
        mimeTypes[".webp"]  = "image/webp";
        mimeTypes[".svg"]   = "image/svg+xml";
        mimeTypes[".ico"]   = "image/x-icon";
        mimeTypes[".mp3"]   = "audio/mpeg";
        mimeTypes[".mp4"]   = "video/mp4";
        mimeTypes[".pdf"]   = "application/pdf";
        mimeTypes[".zip"]   = "application/zip";
        mimeTypes[".rar"]   = "application/vnd.rar";
        mimeTypes[".tar"]   = "application/x-tar";
        contentType = "application/octet-stream";
        std::map<std::string, std::string>::const_iterator it;
        for (it = mimeTypes.begin(); it != mimeTypes.end(); ++it)
        {
            if (it->first == extension)
                contentType = mimeTypes[extension];
        }
        return (contentType);
    }
}