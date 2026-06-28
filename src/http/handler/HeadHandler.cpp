/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeadHandler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 17:02:53 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/29 00:26:31 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HeadHandler.hpp"
#include "IResponse.hpp"

namespace http
{
	HeadHandler::HeadHandler(ResponseFactory &factory) : _getHandler(factory) {}

	HeadHandler::~HeadHandler() {}

	http::IResponse *HeadHandler::handle(const config::ConfigServer *config, const config::ConfigLocation *configLoc,
		http::Request *request) const
	{
		http::IResponse *response;

		response = this->_getHandler.handle(config, configLoc, request);
		response->clearBody();
		return (response);
	}
}