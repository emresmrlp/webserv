/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:06:16 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/27 16:26:30 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigServer.hpp"

namespace config
{
	ConfigServer::ConfigServer()
		: _port(0), _host(""), _root(""), _httpVersion("HTTP/1.1"),
		_maxHeaderSize(8000), _maxBodySize(10000)
		{
			this->_signature = "Webserv0.2.0";
		}

	ConfigServer::~ConfigServer() {}

	int ConfigServer::getPort() const
	{
		return _port;
	}

	const std::string	&ConfigServer::getHttpVersion() const
	{
		return _httpVersion;
	}

	const std::string& ConfigServer::getHost() const
	{
		return _host;
	}

	const std::vector<std::string>& ConfigServer::getServerNames() const
	{
		return _serverNames;
	}

	const std::string& ConfigServer::getRoot() const
	{
		return _root;
	}

	const std::vector<ConfigLocation>& ConfigServer::getLocations() const
	{
		return _locations;
	}

	const ConfigLocation& ConfigServer::getLocation(std::string path) const
	{
		std::vector<config::ConfigLocation>::const_iterator it = _locations.begin();
		while (it != _locations.end())
		{
			if (it->getExecutePath() == path)
				return (*it);
			it++;
		}
		throw std::runtime_error("Error: Location not found");
	}
	
	const std::string &ConfigServer::getSignature() const
	{
		return _signature;
	}

	void ConfigServer::setPort(int port)
	{
		_port = port;
	}

	void ConfigServer::setHost(const std::string& host)
	{
		_host = host;
	}

	void ConfigServer::setServerNames(const std::vector<std::string>& serverNames)
	{
		_serverNames = serverNames;
	}

	void ConfigServer::setRoot(const std::string& root)
	{
		_root = root;
	}

	void ConfigServer::setLocations(const std::vector<ConfigLocation>& locations)
	{
		_locations = locations;
	}
}