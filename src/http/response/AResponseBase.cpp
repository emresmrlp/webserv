/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AResponseBase.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:31:53 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/13 22:19:23 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AResponseBase.hpp"
#include "Util.hpp"
#include <fstream>
#include "Server.hpp"
#include <iostream>
#include <ctime>

namespace http
{
	AResponseBase::AResponseBase(const config::ConfigServer &config, const http::Request *request)
		: _statusCode(http::UNDEFINED), _body(""), _config(config), 
		_signature(this->_config.getSignature()), _request(request)
	{
		this->initDefaultHeaders();
	}

	std::string AResponseBase::serialize() const
	{
		std::ostringstream response;
		
		response << this->buildStatusLine();
		response << this->buildHeader();
		response << this->_body;
		std::cout << "---------------- RESPONSE ----------------" << std::endl;
		std::cout << response.str() << std::endl;
		std::cout << "---------------- RESPONSE END ----------------" << std::endl;
		std::cout << std::endl;
		return (response.str());
	}

	std::string AResponseBase::buildStatusLine() const
	{
		std::ostringstream statusLine;

		statusLine	<< this->_config.getHttpVersion() << " "
				<< this->_statusCode << " "
				<< this->getStatusMessage(this->_statusCode) << CRLF;

		return (statusLine.str());
	}

	std::string	AResponseBase::buildHeader() const
	{
		std::ostringstream header;
		
		std::vector<std::pair<std::string, std::string> >::const_iterator it;
		std::string headerKey;
		for (it = this->_headers.begin(); it != this->_headers.end(); ++it)
		{
			headerKey = it->first;
			header << headerKey << ": " << it->second << CRLF;
		}
		header << CRLF;
		return (header.str());
	}

	void AResponseBase::initDefaultHeaders()
	{
		this->addHeader("Date", util::getCurrentDate());
		this->addHeader("Server", this->_signature);
		this->addHeader("Connection", "close");
	}
	
	void	AResponseBase::clearBody()
	{
		this->_body = "";
	}

	void	AResponseBase::addHeader(const std::string &key, const std::string &value)
	{
		std::pair<std::string, std::string> headerPair;
		headerPair.first = key;
		headerPair.second = value;
		this->_headers.push_back(headerPair);
	}

	void	AResponseBase::setBody(const std::string &body)
	{
		this->_body.clear();
		this->_body = body;
	}

	bool	AResponseBase::getHeader(const std::string &key, std::string &value) const
	{
		std::string fixedKey = key;
		std::vector<std::pair<std::string, std::string> >::const_iterator it;

		util::toLowerCase(fixedKey);
		for (it = this->_headers.begin(); it != this->_headers.end(); ++it)
		{
			if (it->first == fixedKey)
			{
				value = it->second;
				break ;
			}
		}
		if (value.empty())
			return (false);
		return (true);
	}

	const std::string AResponseBase::getMimeType(const std::string &path) const
    {
        std::string contentType;
        std::string extension;
		std::size_t	dotPos;

		dotPos = path.find_last_of(".");
		if (dotPos == std::string::npos)
			return "application/octet-stream";

        extension = path.substr(dotPos);
        static std::map<std::string, std::string> mimeTypes;
		if (mimeTypes.empty())
		{
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
		}
        std::map<std::string, std::string>::const_iterator it;
        for (it = mimeTypes.begin(); it != mimeTypes.end(); ++it)
        {
            if (it->first == extension)
                return (mimeTypes[extension]);
        }
        return "application/octet-stream";
    }

	void AResponseBase::createBody()
    {
        std::string path;

        path = this->_config.getRoot() + this->_request->getPath();
		if (!path.empty())
        	this->setBody(this->readFile(path));
    }

	void AResponseBase::createBody(const std::string &path)
    {
		if (!path.empty())
        	this->setBody(this->readFile(path));
    }

	std::string AResponseBase::readFile(const std::string &filePath)
	{
        std::ifstream file(filePath.c_str(), std::ios::in | std::ios::binary);
        if (!file.is_open())
            return "";
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        return (buffer.str());
    }

	bool	AResponseBase::getHeaders(const std::string &key, std::vector<std::string> &values) const
	{
		std::string fixedKey = key;
		std::vector<std::pair<std::string, std::string> >::const_iterator it;

		util::toLowerCase(fixedKey);
		for (it = this->_headers.begin(); it != this->_headers.end(); ++it)
		{
			if (it->first == fixedKey)
				values.push_back(it->second);
		}
		if (values.empty())
			return (false);
		return (true);
	}

	http::StatusCode AResponseBase::getStatusCode() const
	{
		return (this->_statusCode);
	}
	
	http::StatusMessage AResponseBase::getStatusMessage(http::StatusCode statusCode) const
	{
		switch (statusCode)
		{
			case 200: return "OK";
			case 201: return "Created";
			case 204: return "No Content";
			case 301: return "Moved Permanently";
			case 302: return "Found";
			case 304: return "Not Modified";
			case 400: return "Bad Request";
			case 401: return "Unauthorized";
			case 403: return "Forbidden";
			case 404: return "Not Found";
			case 405: return "Method Not Allowed";
			case 408: return "Request Timeout";
			case 413: return "Payload Too Large";
			case 414: return "URI Too Long";
			case 500: return "Internal Server Error";
			case 501: return "Not Implemented";
			case 502: return "Bad Gateway";
			case 503: return "Service Unavailable";
			case 504: return "Gateway Timeout";
			case 505: return "HTTP Version Not Supported";
			default:  return "Unknown Status";
		}
	};
}