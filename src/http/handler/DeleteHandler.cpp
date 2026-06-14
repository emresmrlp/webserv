/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 17:02:19 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/14 10:59:56 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DeleteHandler.hpp"
#include "ResponseFactory.hpp"
#include <unistd.h>

namespace http
{
	DeleteHandler::DeleteHandler(ResponseFactory &factory) : _factory(factory) {}

	DeleteHandler::~DeleteHandler() {}

	http::IResponse *DeleteHandler::handle(const config::ConfigServer *config, const config::ConfigLocation *,
		http::Request *request) const
	{
		std::string		fileName = config->getRoot() + request->getPath();

		if (unlink(fileName.c_str()) == 0)
			return (this->_factory.createSuccessResponse(config, request, http::NO_CONTENT));
		return (this->_factory.createStatusResponse(config, request, http::NOT_FOUND));
	}
}