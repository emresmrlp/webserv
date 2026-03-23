/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:06:16 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/23 15:44:15 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigServer.hpp"

namespace config
{
	ConfigServer::ConfigServer()
		: _port(0), _host(""), _root("") {}

	ConfigServer::~ConfigServer() {}

	int ConfigServer::getPort() const {
		return _port;
	}

	const std::string& ConfigServer::getHost() const {
		return _host;
	}

	const std::vector<std::string>& ConfigServer::getServerNames() const {
		return _serverNames;
	}

	const std::string& ConfigServer::getRoot() const {
		return _root;
	}

	const std::vector<ConfigLocation>& ConfigServer::getLocations() const {
		return _locations;
	}

	void ConfigServer::setPort(int port) {
		_port = port;
	}

	void ConfigServer::setHost(const std::string& host) {
		_host = host;
	}

	void ConfigServer::setServerNames(const std::vector<std::string>& serverNames) {
		_serverNames = serverNames;
	}

	void ConfigServer::setRoot(const std::string& root) {
		_root = root;
	}

	void ConfigServer::setLocations(const std::vector<ConfigLocation>& locations) {
		_locations = locations;
	}
}