/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 08:21:24 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/19 08:12:59 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include <string>

Request::Request() : _method(""), _path(""), _version(""), _headers(), _bodySize(0), _body(""), _empty("") {}

Request::~Request() {}

Request::Request(const Request &ref) : _method(ref._method), _path(ref._path),
    _version(ref._version), _headers(ref._headers), _bodySize(0), _body(""), _empty("") {}

Request &Request::operator=(const Request &ref)
{
    if (this != &ref)
	{
		this->_method = ref._method;
        this->_path = ref._path;
        this->_version = ref._version;
        this->_headers = ref._headers;
	}
	return (*this);
}

StatusCode  Request::parse(std::string &rawReadBuffer)
{
    
    std::size_t endOfHeader = rawReadBuffer.find(DOUBLE_CRLF);
    std::size_t nextPos = rawReadBuffer.find(CRLF);
    std::string line = rawReadBuffer.substr(0, nextPos);
    std::size_t sp1 = line.find(' ');
    if (sp1 == std::string::npos)
        return (BAD_REQUEST);
    std::size_t sp2 = line.find(' ', sp1 + 1);
    if (sp2 == std::string::npos)
        return (BAD_REQUEST);
    if (line.find(" ", sp2 + 1) != std::string::npos)
        return (BAD_REQUEST); // 2+ SPACE SITUATION
    this->_method = line.substr(0, sp1);
    this->_path = line.substr(sp1 + 1, sp2 - sp1 - 1);
    this->_version = line.substr(sp2 + 1);
    if (this->_method.empty() || this->_path.empty() || this->_version.empty())
        return (BAD_REQUEST);
    // TODO: METHOD VALIDATE (NEED CONF FILE)
    if (this->_method != ALLOWED_METHODS)
        return (METHOD_NOT_ALLOWED);
    // TODO: PATH VALIDATE
    if (this->_path.find("..") != std::string::npos)
        return (FORBIDDEN); // SECURITY REASONS (root access ../)
    if (this->_version != "HTTP/1.1")
        return (HTTP_VERSION_NOT_SUPPORTED);
    std::size_t pos = nextPos + 2;
    while (pos < endOfHeader)
    {
        nextPos = rawReadBuffer.find("\r\n", pos);
        if (nextPos == std::string::npos)
            break ;
        line = rawReadBuffer.substr(pos, nextPos - pos);
        if (line.empty())
            break ;
        std::size_t sep = line.find(":");
        if (sep == std::string::npos)
            return (BAD_REQUEST);
        std::string key = line.substr(0, sep);
        std::string value = line.substr(sep + 1);
        if (key.empty() || value.empty())
            return (BAD_REQUEST);
        for (std::size_t i = 0; i < key.length(); ++i)
            key[i] = std::tolower(static_cast<unsigned char>(key[i]));
        std::size_t firstSpace = value.find_first_not_of(" ");
        if (firstSpace != std::string::npos)
            value = value.substr(firstSpace);
        else
            value = "";
        this->_headers[key] = value;
        pos = nextPos + 2;
    }
    if (this->getHeader("host").empty())
        return (BAD_REQUEST);
    return (OK);
}

void Request::setBodySize(std::size_t bodySize)
{
    if (bodySize > 0)
        this->_bodySize = bodySize;
}

const std::string &Request::getMethod() const { return (this->_method); }

const std::string &Request::getPath() const { return (this->_path); }

const std::string &Request::getVersion() const { return (this->_version); }

const std::string &Request::getHeader(const std::string &key) const
{
    std::string fixedKey = key;

    for (std::size_t i = 0; i < fixedKey.length(); ++i)
        fixedKey[i] = std::tolower(static_cast<unsigned char>(fixedKey[i]));
    std::map<std::string, std::string>::const_iterator it = _headers.find(fixedKey);
    if (it != _headers.end())
        return (it->second);
    return (this->_empty);
}

const std::size_t &Request::getBodySize() const { return (this->_bodySize); }

const std::string &Request::getBody() const { return (this->_body); }