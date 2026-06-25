/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:35:30 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/25 11:19:43 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerHandler.hpp"
#include "ConfigLocation.hpp"
#include "ConfigServer.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <fcntl.h>
#include <csignal>
#include <vector>

namespace core
{
	bool ServerHandler::_running = true;
	
	ServerHandler::ServerHandler() {}

	ServerHandler::~ServerHandler()
	{
		typedef std::vector<Server *>::iterator ServerIt;
		typedef std::vector<Connection *>::iterator ConnectionIt;

		for (ServerIt SIt = this->_servers.begin(); SIt != this->_servers.end(); SIt++)
			delete (*SIt);
		for (ConnectionIt CIt = this->_connnections.begin(); CIt != this->_connnections.end(); CIt++)
			delete (*CIt);
		
		this->_servers.clear();
		this->_connnections.clear();
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

				struct pollfd pollFd;
				pollFd.fd = newServer->getListenFd();
				pollFd.events = POLLIN;
				pollFd.revents = 0;
				this->_pollFds.push_back(pollFd);
			}
		}

		// ! DEBUGGING
		for (size_t i = 0; i < this->_servers.size(); i++)
		{
			std::cout << "Server " << i + 1 << ": " << std::endl;
			uint32_t ip_net = this->_servers[i]->getAddr().ip;
			uint32_t ip_host = ((ip_net & 0x000000FFu) << 24) |
						((ip_net & 0x0000FF00u) << 8)  |
						((ip_net & 0x00FF0000u) >> 8)  |
						((ip_net & 0xFF000000u) >> 24);
			std::cout << "  IP: " << ((ip_host >> 24) & 0xFF) << "." << ((ip_host >> 16) & 0xFF) << "." << ((ip_host >> 8) & 0xFF) << "." << (ip_host & 0xFF) << std::endl;
			uint16_t port_net = this->_servers[i]->getAddr().port;
			uint16_t port_host = (uint16_t)(((port_net & 0x00FFu) << 8) | ((port_net & 0xFF00u) >> 8));
			std::cout << "  Port: " << port_host << std::endl;
			std::cout << "  Server Names: ";
			const std::vector<std::string> &serverNames = this->_servers[i]->getConfig().getServerNames();
			for (size_t j = 0; j < serverNames.size(); j++)
				std::cout << serverNames[j] << (j < serverNames.size() - 1 ? ", " : "");
			std::cout << std::endl;
		}
		// ! END OF DEBUGGING
	}

	void ServerHandler::signalHandler(int)
	{
		ServerHandler::_running = false;
	}

	void ServerHandler::run()
	{
		std::signal(SIGINT, ServerHandler::signalHandler);
		std::signal(SIGTERM, ServerHandler::signalHandler);

		while (ServerHandler::_running)
		{
			int socketCount;

			socketCount = poll(&(this->_pollFds[0]), this->_pollFds.size(), 30000);

			if (socketCount < 0) // ? if poll error occured
			{
				if (ServerHandler::_running == false)
				{
					std::cout << "\nServer closing... Goodbye! (YECS - BME WebServ)" << std::endl;
					break ;
				}
				throw std::runtime_error("ServerHandler(Fatal Error): poll failure.");
			}
			if (socketCount == 0) // ? if no active sockets
			{
				for (std::size_t i = 0; i < this->_pollFds.size(); i++)
				{
					if (i < this->_servers.size())
						continue;
					this->_connnections[i - this->_servers.size()]->handleTimeout();
					this->_pollFds[i].events |= POLLOUT;
				}
			}
			if (socketCount > 0)
			{
				for (std::size_t i = 0; ((i < this->_pollFds.size()) && (socketCount > 0)); i++)
				{
					if (this->_pollFds[i].revents != 0)
					{
						dispatch(i);
						socketCount--;
					}
				}
			}
		}
	}

	void ServerHandler::dispatch(std::size_t i)
	{
		// ? is a server socket? (server socket only listen, cant pollout)
		if (i < this->_servers.size()) // ? if smaller, it means this is a server
		{
			if (this->_pollFds[i].revents & POLLIN)
				this->acceptConnection(i);
			return ;
		}

		// ? connection error control
		if (this->_pollFds[i].revents & (POLLERR | POLLHUP))
		{
			this->closeConnection(i);
			return ;
		}

		// ? connection socket ->
		// ? POLLIN meaning is reading socket
		if (this->_pollFds[i].revents & POLLIN)
			this->readConnection(i);
		// ? POLLOUT meaning is writing socket
		if (this->_pollFds[i].revents & POLLOUT)
			this->writeConnection(i);
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

	void ServerHandler::readConnection(std::size_t i) // ? read request
	{
		std::cout << "Read occured" << std::endl;
		Connection *conn = this->_connnections[i - this->_servers.size()];

		if (conn->getState() == core::CLOSING)
		{
			this->closeConnection(i);
			return ;
		}

		char buffer[4096];
		ssize_t bytesRead = recv(this->_pollFds[i].fd, buffer, sizeof(buffer), 0);

		if (bytesRead > 0)
		{
			std::string rawData(buffer, bytesRead);
			conn->appendRequestBuffer(rawData);
			conn->process();
			if (conn->getState() == core::WRITING)
				this->_pollFds[i].events |= POLLOUT; // ? ready to writeConnection function
		}
		else if (bytesRead <= 0) // ? connection is closed (== 0) or error occured (< 0)
			this->closeConnection(i);
	}

	void ServerHandler::writeConnection(std::size_t i) // ? send response
	{
		Connection *conn = this->_connnections[i - this->_servers.size()];

		const std::string &response = conn->getResponseBuffer();
		if (response.empty())
			return ;
		
		if (conn->getState() != core::WRITING && conn->getState() != core::TIMEOUT)
			return ;
		
		std::size_t remaining = response.length() - conn->getSentBytes();
		if (remaining == 0)
			return ;
		
		ssize_t bytesSent = send(this->_pollFds[i].fd, response.c_str() + conn->getSentBytes(), response.length(), 0);
		if (bytesSent > 0)
		{
			if (static_cast<std::size_t>(bytesSent) == remaining)
			{
				if (conn->getState() == core::TIMEOUT)
				{
					this->closeConnection(i);
					return ;
				}
				conn->resetForNextRequest();
				this->_pollFds[i].events &= ~POLLOUT; // ? (~) meaining opposite (0010) -> (1101)
				std::cout << "Write success. FD: " << this->_pollFds[i].fd << std::endl; 
			}
			else
				conn->eraseResponseBuffer(bytesSent);
		}
		else if (bytesSent < 0)
			this->closeConnection(i);
	}

	void ServerHandler::acceptConnection(std::size_t i)
	{
		// ? accept new connection
		int connFd = accept(this->_pollFds[i].fd, NULL, NULL);
		if (connFd < 0)
			return ;

		// ? set fd settings to non blocking server
		if (fcntl(connFd, F_SETFL, O_NONBLOCK) < 0)
		{
			close(connFd);
			return ;
		}

		// ? create pollfd for connection
		struct pollfd connPollFd;
		connPollFd.fd = connFd;
		connPollFd.events = POLLIN; // ? this case, just reading
		connPollFd.revents = 0;
		this->_pollFds.push_back(connPollFd);

		// ? create connection object
		Connection *newConn = new Connection(connFd);
		newConn->setConfig(&(this->_servers[i]->getConfig()));
		this->_connnections.push_back(newConn);

		std::cout << "New connection created! FD:" << connFd << std::endl;
	}

	void ServerHandler::closeConnection(std::size_t i)
	{
		int connIdx = i - this->_servers.size();

		if (i >= this->_pollFds.size())
			return ;
		if(this->_pollFds[i].fd >= 0)
			close(this->_pollFds[i].fd);

		if (this->_connnections[connIdx] != NULL)
		{
			delete (this->_connnections[connIdx]);
			this->_connnections[connIdx] = NULL;
		}

		this->_pollFds.erase(this->_pollFds.begin() + i);
		this->_connnections.erase(this->_connnections.begin() + connIdx);
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
