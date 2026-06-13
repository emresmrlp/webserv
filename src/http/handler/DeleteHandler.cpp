/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 17:02:19 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/13 20:56:54 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DeleteHandler.hpp"

namespace http
{
    DeleteHandler::DeleteHandler(ResponseFactory &factory) : _factory(factory)
    {
    }

    DeleteHandler::~DeleteHandler()
    {
    }

    http::IResponse *DeleteHandler::handle(const config::ConfigServer *config, const config::ConfigLocation *configLoc,
		http::Request *request) const
	{}
}