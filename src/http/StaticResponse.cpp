/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticResponse.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:26 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/18 22:40:01 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StaticResponse.hpp"
#include "StatusCode.hpp"
#include <iostream>

StaticResponse::StaticResponse(Request &request) : _request(request)
{
    this->_statusCode = OK;
    this->_statusMessage = this->getStatusMessage(this->_statusCode);
}

std::string StaticResponse::serialize() const
{
    std::stringstream response;
    response << HTTP_VERSION << " " << this->_statusCode << " " << this->_statusMessage << "\r\n";
    (void)_request;
    //TODO: PARSE F. READBUFFER TO RETURN WRITEBUFFER.
    return (response.str());
}