/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AResponseBase.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:31:53 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/19 13:12:24 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AResponseBase.hpp"
#include <iostream>
#include <ctime>

std::string AResponseBase::getStatusMessage(StatusCode statusCode)
{
	switch (statusCode)
	{
		case 200: return "OK";
		case 201: return "Created";
		case 204: return "No Content";
		case 301: return "Moved Permanently";
		case 302: return "Found";
		case 304: return "Not Modified";
		case 400: return "Bad Request";
		case 401: return "Unauthorized";
		case 403: return "Forbidden";
		case 404: return "Not Found";
		case 405: return "Method Not Allowed";
		case 408: return "Request Timeout";
		case 413: return "Payload Too Large";
		case 414: return "URI Too Long";
		case 500: return "Internal Server Error";
		case 501: return "Not Implemented";
		case 502: return "Bad Gateway";
		case 503: return "Service Unavailable";
		case 504: return "Gateway Timeout";
		case 505: return "HTTP Version Not Supported";
		default:  return "Unknown Status";
	}
}

std::string AResponseBase::getCurrentDate() const
{
	char	buffer[50];
	time_t	timestamp;

	timestamp = time(NULL);
	std::strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", localtime(&timestamp));
	return (buffer);
}

StatusCode AResponseBase::getStatusCode() const
{
	return (this->_statusCode);
}