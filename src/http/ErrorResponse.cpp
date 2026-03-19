/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorResponse.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:26 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/19 08:11:52 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ErrorResponse.hpp"
#include <iostream>

ErrorResponse::ErrorResponse(StatusCode status)
{
	this->_statusCode = status;
	this->_statusMessage = this->getStatusMessage(this->_statusCode);
}

std::string ErrorResponse::serialize() const
{
	std::ostringstream body_oss;
	body_oss << "<!DOCTYPE html><html lang=\"tr\"><head><meta charset=\"UTF-8\">"
			<< "<title>" << this->_statusCode << " - " << this->_statusMessage << "</title>"
			<< "<style> * { box-sizing: border-box; }"
				"body { font-family: -apple-system, system-ui, sans-serif; display: flex; justify-content: center; align-items: center; height: 100vh; margin: 0; background: #121212; color: #eeeeee; }"
				".box { text-align: center; padding: 60px 40px; background: #1e1e1e; border-radius: 12px; border-top: 6px solid #ef4444; max-width: 480px; width: 90%; box-shadow: 0 20px 50px rgba(0,0,0,0.5); }"
				".brand { font-weight: 800; letter-spacing: 3px; margin-bottom: 15px; font-size: 13px; color: #ef4444; text-transform: uppercase; }"
				"h1 { font-size: 110px; margin: 0; letter-spacing: -4px; font-weight: 900; line-height: 0.9; color: #ffffff; }"
				"p { font-size: 22px; font-weight: 400; margin: 15px 0 35px 0; color: #aaaaaa; }"
				".footer { font-size: 11px; border-top: 1px solid #333; padding-top: 25px; text-transform: uppercase; letter-spacing: 1.5px; color: #666; }"
				"b { color: #888; } </style></head><body>"
			<< "<div class=\"box\"><div class=\"brand\">WEBSERV — HEY LISTEN()!</div>"
			<< "<h1>" << this->_statusCode << "</h1>"
			<< "<p>" << this->_statusMessage << "</p>"
			<< "<div class=\"footer\">Developed by <b>ysumeral, etorun, hhaciogl (C) 2026</b></div>"
			<< "</div></body></html>";
	std::ostringstream response;
	response << HTTP_VERSION << " " << this->_statusCode << " " << this->_statusMessage << CRLF;
	response << "Date: " << this->getCurrentDate() << CRLF;
	response << "Server: " << SERVER_NAME << CRLF;
	if (this->_statusCode == METHOD_NOT_ALLOWED)
		response << "Allow: " << ALLOWED_METHODS << CRLF;
	response << "Content-Type: " << "text/html" << CRLF;
	response << "Content-Length: " << body_oss.str().length() << CRLF;
	response << "Connection: " << "close" << CRLF;
	response << CRLF;
	//TODO: NEED TO DATE AND CONNECT SECTION
	response << body_oss.str();
	return (response.str());
}