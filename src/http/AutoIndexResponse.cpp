/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AutoIndexResponse.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:26 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/19 13:50:12 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AutoIndexResponse.hpp"
#include <iostream>

AutoIndexResponse::AutoIndexResponse()
{
	this->_statusCode = OK;
	this->_statusMessage = this->getStatusMessage(this->_statusCode);
}

std::string AutoIndexResponse::serialize() const
{
	std::ostringstream response;
    response << "autoindex";
	return (response.str());
}