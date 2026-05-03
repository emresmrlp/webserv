/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:06:16 by ysumeral          #+#    #+#             */
/*   Updated: 2026/05/03 18:07:24 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigServer.hpp"
#include <iostream> // ! delete

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

	const config::ConfigLocation& ConfigServer::getLocation(std::string path) const
	{
		if (path.empty())
			path = "/";
		std::vector<config::ConfigLocation>::const_iterator it = _locations.begin();
		while (it != _locations.end())
		{
			if (it->getExecutePath() == path || ("/" + it->getExecutePath()) == path)
				return (*it);
			it++;
		}

		size_t last_slash = path.find_last_of('/');
		if (last_slash == std::string::npos || path == "/")
			return (getLocation("/")); 

		std::string parent_path = path.substr(0, last_slash);
		if (parent_path.empty())
			parent_path = "/";
		return (getLocation(parent_path));
	}
	
	const std::string &ConfigServer::getSignature() const
	{
		return _signature;
	}

	std::size_t	ConfigServer::getMaxHeaderSize() const
	{
		return _maxHeaderSize;
	}

	std::size_t	ConfigServer::getMaxBodySize() const
	{
		return _maxBodySize;
	}

	void ConfigServer::setPort(int port)
	{
		_port = port;
	}

	void ConfigServer::setHost(const std::string& host)
	{
		_host = host;
	}

	void	ConfigServer::addServerName(const std::string& serverName)
	{
		_serverNames.push_back(serverName);
	}

	/*void ConfigServer::setServerNames(const std::vector<std::string>& serverNames)
	{
		_serverNames = serverNames;
	}*/

	void ConfigServer::setRoot(const std::string& root)
	{
		_root = root;
	}

	void	ConfigServer::addLocation(const ConfigLocation& location)
	{
		_locations.push_back(location);
	}

	/*void ConfigServer::setLocations(const std::vector<ConfigLocation>& locations)
	{
		_locations = locations;
	}*/
}