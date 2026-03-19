/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 08:21:24 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/19 15:16:24 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include <string>

Request::Request() : _method(""), _path(""), _version(""), _statusCode(UNDEFINED), _requestParseStatus(INCOMPLETE), _headers(), _bodySize(0), _body(""), _empty("") {}

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

void Request::syncStatus(StatusCode statusCode, RequestParseStatus requestParseStatus)
{
    this->_statusCode = statusCode;
    this->_requestParseStatus = requestParseStatus;
}

//TODO: OPTIMISE PARSER
void    Request::parse(std::string &rawReadBuffer) // ONLY GET PARSE (HEADER)
{
    std::size_t endOfHeader = rawReadBuffer.find(DOUBLE_CRLF);
    if (endOfHeader == std::string::npos)
	{
		if (rawReadBuffer.size() > MAX_HEADER_SIZE)
            return (syncStatus(PAYLOAD_TOO_LARGE, ERROR));
        return (syncStatus(UNDEFINED, INCOMPLETE));
	}
    std::size_t nextPos = rawReadBuffer.find(CRLF);
    std::string line = rawReadBuffer.substr(0, nextPos);
    std::size_t sp1 = line.find(' ');
    std::size_t sp2 = line.find(' ', sp1 + 1);
    if (sp1 == std::string::npos || sp2 == std::string::npos
        || line.find(" ", sp2 + 1) != std::string::npos)
        return (syncStatus(BAD_REQUEST, ERROR));
    this->_method = line.substr(0, sp1);
    this->_path = line.substr(sp1 + 1, sp2 - sp1 - 1);
    this->_version = line.substr(sp2 + 1);
    if (this->_method.empty() || this->_path.empty() || this->_version.empty())
        return (syncStatus(BAD_REQUEST, ERROR));
    // TODO: METHOD VALIDATE (NEED CONF FILE)
    if (this->_method != ALLOWED_METHODS)
        return (syncStatus(METHOD_NOT_ALLOWED, ERROR));
    // TODO: PATH VALIDATE
    if (this->_path.find("..") != std::string::npos)
        return (syncStatus(FORBIDDEN, ERROR));
    if (this->_version != "HTTP/1.1")
        return (syncStatus(HTTP_VERSION_NOT_SUPPORTED, ERROR));
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
            return (syncStatus(BAD_REQUEST, ERROR));
        std::string key = line.substr(0, sep);
        std::string value = line.substr(sep + 1);
        if (key.empty() || value.empty())
            return (syncStatus(BAD_REQUEST, ERROR));
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
        return (syncStatus(BAD_REQUEST, ERROR));
    return (syncStatus(OK, FINISHED));
}

const std::string &Request::getMethod() const { return (this->_method); }

const std::string &Request::getPath() const { return (this->_path); }

const std::string   &Request::getVersion() const { return (this->_version); }

StatusCode          Request::getStatusCode() const { return (this->_statusCode); }

RequestParseStatus  Request::getRequestParseStatus() const { return (this->_requestParseStatus); }

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