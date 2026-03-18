/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorResponse.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:26 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/18 16:21:57 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ErrorResponse.hpp"
#include <iostream>

ErrorResponse::ErrorResponse() { std::cout << "ERROR RESPOSONSE ACTIVE code is: " << this->_statusCode << std::endl;}

std::string ErrorResponse::serialize() const
{
    const std::string empty("");
    return (empty);
}