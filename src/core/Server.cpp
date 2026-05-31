/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:35:32 by ysumeral          #+#    #+#             */
/*   Updated: 2026/05/31 15:32:22 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

namespace core
{
	Server::Server(const config::ConfigServer &config, const HostAddr &addr)
		: _addr(addr), _listenFd(-1), _config(config) {}

	Server::~Server()
	{
		if (this->_listenFd != -1)
			close(this->_listenFd);
	}

	void Server::setup()
	{
		this->_listenFd = socket(AF_INET, SOCK_STREAM, 0); // ? for create new socket
		if (this->_listenFd == -1)
			throw std::runtime_error("Failed to create socket.");

		int opt = 1;
		if (setsockopt(this->_listenFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) // ? for reuse address option to true (fixing already using problem ex/ ctrl + c)
			throw std::runtime_error("Reuse address option failed on sockopt.");

		struct sockaddr_in serverAddr;
		std::memset(&serverAddr, 0, sizeof(serverAddr));
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_addr.s_addr = this->_addr.ip;
		serverAddr.sin_port = this->_addr.port;

		if (bind(this->_listenFd, reinterpret_cast<sockaddr *>(&serverAddr), sizeof(serverAddr)) < 0) // ? for bind address to socket
			throw std::runtime_error("Bind failed. Port already using.");
		
		if (listen(this->_listenFd, 128) < 0) // ? open to connect for Server.
			throw std::runtime_error("Listen failed.");
	}

	const HostAddr &Server::getAddr() const
	{
		return (this->_addr);
	}
	

	int	Server::getListenFd() const
	{
		return (this->_listenFd);
	}

	const config::ConfigServer &Server::getConfig() const
	{
		return (this->_config);
	}
}