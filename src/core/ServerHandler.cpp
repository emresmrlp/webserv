/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:35:30 by ysumeral          #+#    #+#             */
/*   Updated: 2026/05/25 16:06:12 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerHandler.hpp"
#include "ConfigLocation.hpp"
#include "ConfigServer.hpp"
#include <vector>

namespace core
{
	ServerHandler::ServerHandler() {}

	const std::vector<core::Server>& ServerHandler::getServers() const
	{
		return (this->_servers);
	}

	ServerHandler::~ServerHandler() {}
}
