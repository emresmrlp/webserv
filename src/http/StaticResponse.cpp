/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticResponse.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:26 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/18 22:09:56 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StaticResponse.hpp"
#include "StatusCode.hpp"
#include <iostream>

StaticResponse::StaticResponse(std::string &readBuffer) : _readBuffer(readBuffer)
{
    this->_statusCode = OK;
    this->_statusMessage = this->getStatusMessage(this->_statusCode);
}

std::string StaticResponse::serialize() const
{
    std::stringstream response;
    response << HTTP_VERSION << " " << this->_statusCode << " " << this->_statusMessage << "\r\n";
    (void)this->_readBuffer;
    //TODO: PARSE F. READBUFFER TO RETURN WRITEBUFFER.
    return (response.str());
}