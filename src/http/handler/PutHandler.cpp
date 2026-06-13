/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PutHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 17:03:06 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/13 20:16:20 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PutHandler.hpp"

namespace http
{
    PutHandler::PutHandler()
    {
    }

    PutHandler::~PutHandler()
    {
    }

    http::IResponse *PutHandler::handle(const config::ConfigServer *config, const config::ConfigLocation *configLoc,
		http::Request *request) const
	{}
}