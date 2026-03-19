/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticResponse.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:26 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/19 08:32:54 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StaticResponse.hpp"
#include "StatusCode.hpp"
#include <iostream>
#include "Request.hpp"
#include <iomanip>
#include <sstream>
#include <fstream>

StaticResponse::StaticResponse(Request &request, std::size_t bodySize) : _request(request), _bodySize(bodySize)
{
    this->_statusCode = OK;
    this->_statusMessage = this->getStatusMessage(this->_statusCode);
}

static std::string readFile(const std::string& filePath) {
    std::ifstream file(filePath.c_str());
    if (!file.is_open())
        return "";
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return (buffer.str());
}

const std::string StaticResponse::createBody() const
{
	std::string filePath = ROOT;
	filePath += this->_request.getPath();
	std::cout << filePath << std::endl;
    return (readFile(filePath));
}

std::string StaticResponse::serialize() const
{
    std::ostringstream body_oss;
    body_oss << createBody();
    std::ostringstream response;
    response << HTTP_VERSION << " " << this->_statusCode << " " << this->_statusMessage << CRLF;
    response << "Date: " << this->getCurrentDate() << CRLF;
	response << "Server: " << SERVER_NAME << CRLF;
	response << "Content-Type: " << "text/html" << CRLF;
	response << "Content-Length: " << this->_bodySize << CRLF;
	response << "Connection: " << "close" << CRLF; // TODO: CHECK THE CONNECTION STATES
    response << CRLF;
    response << body_oss.str();
    //TODO: PARSE F. READBUFFER TO RETURN WRITEBUFFER.
    return (response.str());
}