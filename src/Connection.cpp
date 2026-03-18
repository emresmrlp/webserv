/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 06:30:45 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/18 09:22:11 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Connection.hpp"
#include <iostream>

Connection::Connection(int fd) : _fd(fd), _state(READING) {}

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
		case SUCCESS:
			std::cout << "HTTP REQUEST PARSE: SUCCESS" << std::endl;
			this->setState(WRITING);
			break;
		case BAD_REQUEST:
			std::cout << "Error: 400 BAD REQUEST" << std::endl;
			break;
		default:
			break;
	}
	//header parse ok
}

HTTPRequest &Connection::getRequest() {return (this->_request); }

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

Connection::Connection(const Connection &ref) { *this = ref; }

Connection &Connection::operator=(const Connection &ref)
{
	if (this != &ref)
	{
		this->_fd = ref._fd;
		this->_state = ref._state;
		this->_readBuffer = ref._readBuffer;
        this->_writeBuffer = ref._writeBuffer;
        this->_request = ref._request;
	}
	return (*this);
}

Connection::Connection() : _fd(-1), _state(CLOSING) {}

Connection::~Connection() {}