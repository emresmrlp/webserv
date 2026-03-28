/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 08:21:24 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/27 18:47:43 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include <string>
#include "Util.hpp"

namespace http
{
    Request::Request() : _method(""), _path(""), _version(""), _headers(), _body("") {}

    Request::~Request() {}

    Request::Request(const Request &ref) : _method(ref._method), _path(ref._path),
        _version(ref._version), _headers(ref._headers), _body("") {}

    Request &Request::operator=(const Request &ref)
    {
        if (this != &ref)
        {
            this->_method = ref._method;
            this->_path = ref._path;
            this->_version = ref._version;
            this->_headers = ref._headers;
            this->_body = ref._body;
        }
        return (*this);
    }

    void Request::addHeader(const std::string &key, const std::string &value)
    {
        std::pair<std::string, std::string> headerPair;
		std::string fixedKey = key;

        util::toLowerCase(fixedKey);
		headerPair.first = fixedKey;
		headerPair.second = value;
		this->_headers.push_back(headerPair);
    }

    void Request::setMethod(const std::string &method) { this->_method = method; }

    void Request::setPath(const std::string &path) { this->_path = path; }

    void Request::setVersion(const std::string &version) { this->_version = version; }

    void Request::setBody(const std::string &body) { this->_body = body; }

    bool	Request::getHeader(const std::string &key, std::string &value) const
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

	bool	Request::getHeaders(const std::string &key, std::vector<std::string> &values) const
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

    const std::string	&Request::getMethod() const { return (this->_method); }

    const std::string	&Request::getPath() const { return (this->_path); }

    const std::string	&Request::getVersion() const { return (this->_version); }

    const std::string	&Request::getBody() const { return (this->_body); }
}