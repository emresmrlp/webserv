/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:35:32 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/27 16:08:07 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

namespace core
{
	Server::Server(config::ConfigServer &config) : _config(config) {}

	Server::~Server()
	{
		if (this->_config)
		{
			delete (this->_config);
			this->_config = NULL;
		}
	}

	const config::ConfigServer &Server::getConfig() const
	{
		return (*(this->_config));
	}
}