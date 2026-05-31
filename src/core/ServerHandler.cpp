/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:35:30 by ysumeral          #+#    #+#             */
/*   Updated: 2026/05/31 15:36:27 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerHandler.hpp"
#include "ConfigLocation.hpp"
#include "ConfigServer.hpp"
#include <vector>

namespace core
{
	ServerHandler::ServerHandler() {}

	ServerHandler::~ServerHandler()
	{
		typedef std::vector<Server *>::iterator ServerIt;

		for (ServerIt it = this->_servers.begin(); it != this->_servers.end(); it++)
			delete (*it);
		
		this->_servers.clear();
	}

	void ServerHandler::init(const std::vector<config::ConfigServer> &_configs)
	{
		HostAddr addr;
		typedef std::vector<config::ConfigServer>::const_iterator ConfigIt;
		typedef std::vector<config::ListenTarget>::const_iterator ListenIt; // ? ConfigServer->ListenTarget iterator

		for (ConfigIt it = _configs.begin(); it != _configs.end(); it++)
		{
			const std::vector<config::ListenTarget> &listens = it->getListens();
			for (ListenIt LIt = listens.begin(); LIt != listens.end(); LIt++)
			{
				addr = resolveHostAddr(LIt->host, LIt->port);
				if (isActiveServer(addr))
					continue;
				Server *newServer = new Server(*it, addr);
				newServer->setup();
				this->_servers.push_back(newServer);
			}
		}
	}

	bool ServerHandler::isActiveServer(HostAddr &addr)
	{
		typedef std::vector<Server *>::const_iterator ServerIt;

		for (ServerIt it = this->_servers.begin(); it != this->_servers.end(); it++)
		{
			if ((*it)->getAddr() == addr)
				return (true);
		}
		return (false);
	}

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
