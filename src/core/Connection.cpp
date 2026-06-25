/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 06:30:45 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/25 11:18:07 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connection.hpp"
#include "SuccessResponse.hpp"
#include "StatusResponse.hpp"
#include <iostream>
#include "Request.hpp"
#include "ResponseDispatcher.hpp"

namespace core
{
	Connection::Connection(int fd) : _fd(fd), _readBuffer(""),  _writeBuffer(""),
		_response(NULL), _request(NULL), _responseFactory(), _dispatcher(_responseFactory), 
		_requestBuilder(), _state(READING), _config(NULL) {}

	void Connection::process()
	{
		std::cout << "+ Connection -> process called. State: " << this->_state << std::endl;
		if (this->_state != READING)
			return ;

		http::ParseResult parseResult;
		parseResult = this->_requestBuilder.parse(this->_readBuffer, this->_config);
		std::cout << "+ Connection -> RequestBuilder process result: " << parseResult.parseStatus << std::endl;
		if (parseResult.parseStatus == http::INCOMPLETE)
			return ;
		this->_request = this->_requestBuilder.build();
		if (parseResult.parseStatus == http::ERROR)
			this->_response = this->_responseFactory.createStatusResponse(this->_config, this->_request, parseResult.httpStatusCode);
		else if (parseResult.parseStatus == http::COMPLETE)
			this->_response = this->_dispatcher.dispatch(this->_config, this->_request);
		this->_writeBuffer = this->_response->serialize();
		this->setState(WRITING);
	}

	void Connection::handleTimeout()
	{
		std::cout << "! DEBUG: TIMEOUT" << std::endl;
		if (!this->_config)
		{
			this->setState(CLOSING);
			return ;
		}
		this->_response = this->_responseFactory.createStatusResponse(this->_config, NULL, http::REQUEST_TIMEOUT);
		this->_writeBuffer = this->_response->serialize();
		this->setState(TIMEOUT);
	}

	void Connection::appendRequestBuffer(const std::string &buffer)
	{	
		this->_readBuffer += buffer;
	}

	void Connection::resetForNextRequest()
	{
		this->_sentBytes = 0;
		this->_readBuffer.clear();
		this->_writeBuffer.clear();

		if (this->_request)
		{
			delete (this->_request);
			this->_request = NULL;
		}
		if (this->_response)
		{
			delete (this->_response);
			this->_response = NULL;
		}
		
		this->_requestBuilder.reset();
		std::cout << "Connection reset success." << std::endl;
		this->_state = READING;
	}

	bool	Connection::hasResponse() const
	{
		if (this->_response != NULL)
			return (true);
		return (false);
	}

	int Connection::getFd() const { return (this->_fd); }
	
	ConnectionState Connection::getState() const { return (this->_state); }

	const std::string	&Connection::getResponseBuffer() const { return (this->_writeBuffer); }
	
	void	Connection::setState(ConnectionState state)
	{
		if (this->_state == state)
			return ;
		if (this->_state == CLOSING)
			return ;
		this->_state = state;
	}

	void	Connection::setConfig(const config::ConfigServer *config)
	{
		this->_config = config;
	}
	
	std::size_t Connection::getSentBytes() const
	{
		return (this->_sentBytes);
	}

	void Connection::eraseResponseBuffer(std::size_t bytesSent)
	{
		this->_sentBytes += bytesSent;
	}

	Connection::~Connection()
	{
		if (this->_response)
		{
			delete (this->_response);
			this->_response = NULL;
		}
		if (this->_request)
		{
			delete (this->_request);
			this->_request = NULL;
		}
	}

}