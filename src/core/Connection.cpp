/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 06:30:45 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/18 16:38:14 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connection.hpp"
#include "StaticResponse.hpp"
#include "ErrorResponse.hpp"
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
	status = this->_request.parse(this->_readBuffer);
	switch (status)
	{
		case OK:
			std::cout << "HTTP REQUEST PARSE: SUCCESS" << std::endl;
			this->setState(WRITING);
			this->handleRequest(status);
			break;
		default:
			std::cout << "Error code: " << status << std::endl;
			break;
	}
}

void	Connection::handleRequest(StatusCode status)
{
	if (status == OK)
		std::cout << "handle request issue" << std::endl;
}

IResponse *Connection::getResponse()
{
	return (_response);
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

Connection::Connection() : _fd(-1), _state(CLOSING) {}

Connection::~Connection() {}