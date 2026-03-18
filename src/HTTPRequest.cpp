/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 08:21:24 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/18 09:38:51 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/HTTPRequest.hpp"
#include <sstream>

HTTPRequest::HTTPRequest() {}

HTTPRequest::~HTTPRequest() {}

HTTPRequest::HTTPRequest(const HTTPRequest &ref) : _method(ref._method), _path(ref._path),
    _version(ref._version), _headers(ref._headers) {}

HTTPRequest &HTTPRequest::operator=(const HTTPRequest &ref)
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

StatusCode  HTTPRequest::parse(std::string &rawReadBuffer)
{
    std::size_t endOfHeader = rawReadBuffer.find("\r\n\r\n");
    if (endOfHeader == std::string::npos)
        return (INCOMPLETE);

    std::size_t nextPos = rawReadBuffer.find("\r\n");
    std::string line = rawReadBuffer.substr(0, nextPos);
    std::stringstream ss(line);
    if (!(ss >> this->_method >> this->_path >> this->_version))
        return (BAD_REQUEST);
    std::string extra;
    if (ss >> extra)
        return (BAD_REQUEST); 

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
    if (this->_version != "HTTP/1.1")
        return (BAD_REQUEST);
    return (SUCCESS);
}

const std::string &HTTPRequest::getMethod() const { return (this->_method); }

const std::string &HTTPRequest::getPath() const { return (this->_path); }

const std::string &HTTPRequest::getVersion() const { return (this->_version); }

const std::string HTTPRequest::getHeader(const std::string &key) const
{
    std::string fixedKey = key;

    for (std::size_t i = 0; i < fixedKey.length(); ++i)
        fixedKey[i] = std::tolower(static_cast<unsigned char>(fixedKey[i]));
    std::map<std::string, std::string>::const_iterator it = _headers.find(fixedKey);
    if (it != _headers.end())
        return (it->second);
    return ("");
}