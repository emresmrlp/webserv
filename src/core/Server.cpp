/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:35:32 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/23 16:21:10 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

namespace core
{
	Server::Server() : _config(NULL) {}

	Server::~Server()
	{
		if (this->_config)
		{
			delete (this->_config);
			this->_config = NULL;
		}
	}

	void Server::init()
	{
		this->_config = new config::ConfigServer();
		this->_config->setHost("localhost");
		this->_config->setPort(8080);
	}

	config::ConfigServer &Server::getConfig()
	{
		return (*(this->_config));
	}
}