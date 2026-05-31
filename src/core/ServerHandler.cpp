/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:35:30 by ysumeral          #+#    #+#             */
/*   Updated: 2026/05/31 14:39:35 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerHandler.hpp"
#include "ConfigLocation.hpp"
#include "ConfigServer.hpp"
#include <vector>

namespace core
{
	ServerHandler::ServerHandler() {}

	ServerHandler::~ServerHandler() {}

	HostAddr ServerHandler::resolveHostAddr(const std::string &ip, int port)
	{
		HostAddr hostAddr;

		struct addrinfo filter;
		struct addrinfo *res;

		std::memset(&filter, 0, sizeof(filter)); // ? for cleaning garbage values
		filter.ai_family = AF_INET;
		filter.ai_socktype = SOCK_STREAM; // ? for TCP Protocol (handshake)

		std::ostringstream portStream;
		portStream << port;

		if (getaddrinfo(ip.c_str(), portStream.str().c_str(), &filter, &res) != 0)
			throw std::runtime_error("Address resolving problem occured.");

		struct sockaddr_in *addr = reinterpret_cast<struct sockaddr_in *>(res->ai_addr); // ? addrinfo address

		hostAddr.ip = addr->sin_addr.s_addr;
		hostAddr.port = addr->sin_port;

		freeaddrinfo(res);

		return (hostAddr);
	}
}
