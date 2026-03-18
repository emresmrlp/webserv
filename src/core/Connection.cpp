/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 06:30:45 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/18 22:05:29 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connection.hpp"
#include "StaticResponse.hpp"
#include "ErrorResponse.hpp"
#include "Config.hpp"
#include <iostream>

Connection::Connection(int fd) : _fd(fd), _state(READING), _response(NULL),
	_readBuffer(""),  _writeBuffer("") {}

void Connection::addReadBuffer(const std::string &buffer)
{	
	this->_readBuffer += buffer;
}

void Connection::update()
{
	StatusCode	status;

	if (this->_state != READING)
		return ;
	std::size_t endOfHeader = this->_readBuffer.find("\r\n\r\n");
	if (endOfHeader == std::string::npos)
	{
		if (this->_readBuffer.size() > MAX_HEADER_SIZE)
			this->handleRequest(PAYLOAD_TOO_LARGE);
		return;
	}
	status = this->_request.parse(this->_readBuffer);
	switch (status)
	{
		case OK:
			std::cout << "HTTP REQUEST PARSE: SUCCESS" << std::endl;
			this->handleRequest(status);
			break;
		default:
			this->handleRequest(status);
			break;
	}
}

void	Connection::handleRequest(StatusCode status)
{
	if (status == OK)
	{
		this->setState(WRITING);
		this->_response = new StaticResponse(this->_readBuffer);
		return ;
	}
	this->setState(ERROR);
	this->_response = new ErrorResponse(status);
}

IResponse *Connection::getResponse()
{
	if (this->_response != NULL)
		return (_response);
	throw NoResponseFoundError();
}

Request &Connection::getRequest() {return (this->_request); }

int Connection::getFd() const { return (this->_fd); }

void    Connection::setState(ConnectionState state)
{
	if (this->_state == state)
		return ;
	if (this->_state == CLOSING)
		return ; 
	this->_state = state;
}

ConnectionState Connection::getState() const { return (this->_state); }

Connection::~Connection()
{
	if (this->_response != NULL) {
		delete (this->_response);
		this->_response = NULL;
	}
}

const char *Connection::NoResponseFoundError::what() const throw()
{
	return "Error: No response found!";
}