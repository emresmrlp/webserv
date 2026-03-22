/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 06:30:45 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/22 21:35:10 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connection.hpp"
#include "StaticResponse.hpp"
#include "AutoIndexResponse.hpp"
#include "ErrorResponse.hpp"
#include "Config.hpp"
#include <iostream>
#include "Request.hpp"
#include "ResponseDispatcher.hpp"

namespace core
{
	Connection::Connection(int fd) : _fd(fd), _readBuffer(""),  _writeBuffer(""),
		_response(NULL), _request(NULL), _dispatcher(_responseFactory), _state(READING) {}

	void Connection::process()
	{
		if (this->_state != READING)
			return ;

		http::ParseResult parseResult;
		parseResult = this->_requestBuilder.parse(this->_readBuffer);
		if (parseResult.parseStatus == http::INCOMPLETE)
			return ;

		if (parseResult.parseStatus == http::ERROR)
			this->_response = this->_responseFactory.createErrorResponse(parseResult.httpStatusCode);
		else
		{
			this->_request = this->_requestBuilder.build();
			this->_response = this->_dispatcher.dispatch(*(this->_request));
		}
		this->_writeBuffer = this->_response->serialize();
		this->setState(WRITING);
	}

	void Connection::appendRequestBuffer(const std::string &buffer)
	{	
		this->_readBuffer += buffer;
	}

	void Connection::resetForNextRequest()
	{
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