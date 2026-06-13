/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestBuilder.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 10:09:04 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/13 21:34:50 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestBuilder.hpp"
#include "Request.hpp"
#include "Util.hpp"
#include <vector>
#include <iostream>

namespace http
{
	RequestBuilder::RequestBuilder() : _state(http::STATE_REQUEST_LINE) {}

	RequestBuilder::~RequestBuilder() {}

	http::ParseResult RequestBuilder::handleParseResult(http::StatusCode statusCode, http::ParseStatus parseStatus)
	{
		if (statusCode == http::BAD_REQUEST)
		{
			std::vector<std::string> headers;
			std::cout << "BAD REQUEST: PATH-" << this->_path << " METHOD-" << this->_method << " VERSION-" << this->_version;
		}
		this->_parseResult.httpStatusCode = statusCode;
		this->_parseResult.parseStatus = parseStatus;
		std::cout << "+ RequestBuilder -> ParseResult_StatusCode: " << statusCode
			<< " ParseResult_ParseStatus: " << parseStatus << std::endl;
		return (this->_parseResult);
	}

	http::ParseResult   RequestBuilder::parse(std::string &rawReadBuffer, const config::ConfigServer *config)
	{
		std::cout << "+ RequestBuilder -> Build starting..." << std::endl;
		// has header? -> REQUEST or HEADERS state
		if (this->_state == http::STATE_REQUEST_LINE
			|| this->_state == http::STATE_HEADERS)
		{
			if (rawReadBuffer.find(DOUBLE_CRLF) == std::string::npos)
			{
				if (rawReadBuffer.size() > config->getMaxHeaderSize())
					return (handleParseResult(PAYLOAD_TOO_LARGE, ERROR));
				return (handleParseResult(UNDEFINED, INCOMPLETE));
			}
		}
		// line by line parse
		std::size_t	nextPos;
		std::string line;
		std::cout << "+ RequestBuilder -> Line by line starting..." << std::endl;
		while (!rawReadBuffer.empty())
		{
			// find CRLF
			nextPos = rawReadBuffer.find(CRLF);
			if (nextPos == std::string::npos)
				break ;
			// request line parse
			if (this->_state == http::STATE_REQUEST_LINE)
			{
				std::cout << "+ RequestBuilder -> Request line parsing..." << std::endl;
				line = rawReadBuffer.substr(0, nextPos);

				if (!(line.empty()) && (line[0] == ' ' || line[0] == '\t'))
					return (handleParseResult(BAD_REQUEST, ERROR));
				if (!buildRequestLine(line))
					return (this->_parseResult);

				rawReadBuffer.erase(0, nextPos + 2); // +2 for CRLF (\r\n)
				std::cout << "+ RequestBuilder -> Request line parsed success." << std::endl;
				this->_state = http::STATE_HEADERS;
			}
			else if (this->_state == http::STATE_HEADERS)
			{
				// if first line is CRLF
				if (nextPos == 0)
				{
					rawReadBuffer.erase(0, 2);
					if (config->getLocation(this->_path)->hasRedirection())
					{
						this->_state = http::STATE_WAIT_VALIDATE;
						handleParseResult(static_cast<http::StatusCode>
							(config->getLocation(this->_path)->getReturnRedirection().first), COMPLETE);
					}
					this->_state = http::STATE_BODY;
					break ;
				}
				line = rawReadBuffer.substr(0, nextPos);

				if (!(line.empty()) && (line[0] == ' ' || line[0] == '\t'))
					return (handleParseResult(BAD_REQUEST, ERROR));
				if (!buildHeaderLine(line))
					return (this->_parseResult);

				rawReadBuffer.erase(0, nextPos + 2); // +2 for CRLF (\r\n)
			}
		}
		if (this->_state == http::STATE_BODY)
		{
			std::cout << "+ RequestBuilder -> Body parsing..." << std::endl;
			if (!rawReadBuffer.empty())
				this->_body = rawReadBuffer;
			this->_state = http::STATE_WAIT_VALIDATE;
		}
		if (this->_state == http::STATE_WAIT_VALIDATE)
		{
			if (!validateParseResult())
				return (this->_parseResult);
			this->_state = http::STATE_COMPLETE;
		}
		if (this->_state == http::STATE_COMPLETE)
			return (handleParseResult(OK, COMPLETE));
		return (handleParseResult(UNDEFINED, INCOMPLETE));
	}

	bool RequestBuilder::buildRequestLine(std::string &line)
	{
		std::cout << "+ RequestBuilder -> buildRequestLine method starting..." << std::endl;
        std::size_t sp1 = line.find(' ');
        std::size_t sp2 = line.find(' ', sp1 + 1);

		// exact 2 spaces no more
        if (sp1 == std::string::npos || sp2 == std::string::npos
            || line.find(" ", sp2 + 1) != std::string::npos)
		{
            handleParseResult(BAD_REQUEST, ERROR);
			return (false);
		}
		
		//request line attr
        this->_method = line.substr(0, sp1);
        this->_path = line.substr(sp1 + 1, sp2 - sp1 - 1);
        this->_version = line.substr(sp2 + 1);
		std::cout << "+ RequestBuilder -> buildRequestLine -> method: " << _method <<
			" path: " << _path << " version: " << _version << std::endl;

		//request line attr controls
        if (this->_method.empty() || this->_path.empty() || this->_version.empty())
		{
            handleParseResult(BAD_REQUEST, ERROR);
			return (false);
		}		
        // path validate
        if (this->_path.find("/../") != std::string::npos // if "root/../pictures"
			|| this->_path.substr(0, 3) == "../" // if "../pictures"
			|| this->_path == ".." // if ".."
			|| (this->_path.length() >= 3 && this->_path.substr(this->_path.length() - 3) == "/..")) // if "root/pictures/.."
		{
            handleParseResult(FORBIDDEN, ERROR);
			return (false);
		}
		// version validate
        if (this->_version != "HTTP/1.1")
        {
			handleParseResult(HTTP_VERSION_NOT_SUPPORTED, ERROR);
			return (false);
		}
		return (true);
	}

	bool RequestBuilder::buildHeaderLine(std::string &line)
	{
		// control line has "key: value" : seperator
		std::size_t sep = line.find(":");
		if (sep == std::string::npos // ":" seperator does not exist
			|| sep == 0) // ": value" state
		{
			handleParseResult(BAD_REQUEST, ERROR);
			return (false);
		}
		std::string key = line.substr(0, sep);
		std::string value = line.substr(sep + 1);
		if (key.find_first_of(" \t") != std::string::npos
			|| key.find(" ") != std::string::npos) // "k ey: value" state
		{
			handleParseResult(BAD_REQUEST, ERROR);
			return (false);
		}
		std::size_t firstSpace = value.find_first_not_of(" \t");
		if (firstSpace == std::string::npos) // if string only " ", "\t" or " \t"
			value = "";
		else
		{
			std::size_t lastSpace = value.find_last_not_of(" \t"); //"key:  value  " is "value  " so we need to delete last spaces.
			value = value.substr(firstSpace, lastSpace + 1);
		}
		// add header
		this->addHeader(key, value);
		return (true);
	}

	bool RequestBuilder::buildBody(std::string &rawReadBuffer)
	{
		if (rawReadBuffer.empty())
			return (false);
		this->_body = rawReadBuffer;
		return (true);
	}

	bool RequestBuilder::validateParseResult()
	{
		std::vector<std::string> values;

		// host validate
		this->getHeaders("host", values);

		if (values[0].empty())
		{
			handleParseResult(BAD_REQUEST, ERROR);
            return (false);
		}
		return (true);
	}

	void	RequestBuilder::addHeader(const std::string &key, const std::string &value)
	{
		std::pair<std::string, std::string> headerPair;
		std::string fixedKey = key;

        util::toLowerCase(fixedKey);
		headerPair.first = fixedKey;
		headerPair.second = value;
		this->_headers.push_back(headerPair);
	}

	bool	RequestBuilder::getHeaders(const std::string &key, std::vector<std::string> &values) const
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

	void    RequestBuilder::appendBody(const std::string &buffer)
	{
		std::string body;
		body += buffer;
		this->_body = body;
	}

	Request *RequestBuilder::build()
	{
		Request *request = new Request();

		request->setMethod(this->_method);
		request->setPath(this->_path);
		request->setVersion(this->_version);
		std::string headerKey;
		std::vector<std::pair<std::string, std::string> >::const_iterator it;
		for (it = this->_headers.begin(); it != this->_headers.end(); ++it)
		{
			headerKey = it->first;
			util::toLowerCase(headerKey);
			request->addHeader(headerKey, it->second);
		}
		request->setBody(this->_body);
		this->reset();
		return (request);
	}

	void RequestBuilder::reset()
	{
		_method.clear();
		_path.clear();
		_version.clear();
		_headers.clear();
		_body.clear();
		this->_state = http::STATE_REQUEST_LINE;
	}
}