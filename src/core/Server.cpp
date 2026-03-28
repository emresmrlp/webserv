/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:35:32 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/28 10:35:38 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

namespace core
{
	Server::Server(const config::ConfigServer &config) : _config(config) {}

	Server::~Server() {}

	const config::ConfigServer &Server::getConfig() const
	{
		return (this->_config);
	}
}