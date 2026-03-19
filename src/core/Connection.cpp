/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 06:30:45 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/19 15:18:39 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connection.hpp"
#include "StaticResponse.hpp"
#include "AutoIndexResponse.hpp"
#include "ErrorResponse.hpp"
#include "Config.hpp"
#include <iostream>
#include <sys/stat.h>

Connection::Connection(int fd) : _fd(fd), _state(READING), _response(NULL),
	_readBuffer(""),  _writeBuffer("") {}

void Connection::addReadBuffer(const std::string &buffer)
{	
	this->_readBuffer += buffer;
}

void Connection::prepareRequest()
{
	this->_request.parse(this->_readBuffer);
}

void	Connection::prepareResponse()
{
	StatusCode status;
	
	if (this->_request.getRequestParseStatus() == INCOMPLETE)
		return ;
	status = this->_request.getStatusCode();
	if (status != OK)
	{
		this->_response = new ErrorResponse(status);
		this->setState(WRITING);
		return ;
	}
	struct stat st;
	// TODO: filePath must be fixed with ConfigLocation
	std::string filePath = ROOT; // TODO
	filePath += this->_request.getPath(); // TODO
	if (stat(filePath.c_str(), &st) != 0)
		this->_response = new ErrorResponse(NOT_FOUND);
	else if (S_ISREG(st.st_mode))
		this->_response = new StaticResponse(this->_request, st.st_size);
	else if (S_ISDIR(st.st_mode))
	{
		if (AUTOINDEX)
			this->_response = new AutoIndexResponse();
		else
			this->_response = new ErrorResponse(FORBIDDEN);
	}
	this->setState(WRITING);
}

IResponse *Connection::getResponse()
{
	if (this->_response != NULL)
		return (_response);
	throw NoResponseFoundError();
}

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