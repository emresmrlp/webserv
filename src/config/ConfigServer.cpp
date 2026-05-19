/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:06:16 by ysumeral          #+#    #+#             */
/*   Updated: 2026/05/19 15:06:07 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/config/ConfigServer.hpp"
#include <iostream>

namespace config
{
	ConfigServer::ConfigServer()
		: _root("/"), _httpVersion("HTTP/1.1"),
		_maxHeaderSize(8000), _maxBodySize(8000), _signature("Webserv0.2.0") { }
	
	ConfigServer::~ConfigServer() { }

	long    ConfigServer::parseByte(std::string str)    const
	{
		if (str.empty())
			return 1024 * 1024;

		char    unit = std::toupper(str[str.length() - 1]);
		long    multiplier = 1;

		if (unit == 'K') multiplier = 1024;
		else if (unit == 'M') multiplier = 1024 * 1024;
		else if (unit == 'G') multiplier = 1024 * 1024 * 1024;
		else if (!std::isdigit(unit)) return -1;
			
		if (unit == 'K' || unit == 'M' || unit == 'G') 
			str.resize(str.length() - 1);

		if (str.empty())
			return -1;

		for (size_t i = 0; i < str.length(); ++i)
			if (!std::isdigit(str[i]))
				return -1;

		long    num = std::atol(str.c_str());

		if (num <= 0)
			return 1024 * 1024;

		return num * multiplier;
	}

	// SETTER FUNCTIONS
	bool	ConfigServer::setRoot(const std::string& root) { _root = root; return true;}
	//bool	ConfigServer::setHttpVersion(const std::string& version) { _httpVersion = version; }
	//bool	ConfigServer::setSignature(const std::string& signature) { _httpVersion = signature; }
	bool	ConfigServer::setMaxHeaderSize(const std::string& str)
		{ _maxHeaderSize = parseByte(str); if (_maxHeaderSize == -1) return false;  return true; }
	bool	ConfigServer::setMaxBodySize(const std::string& str)
		{ _maxBodySize = parseByte(str); if (_maxBodySize == -1) return false;  return true; }

	void	ConfigServer::addServerName(const std::string& serverName) { _serverNames.push_back(serverName); }
	void	ConfigServer::addLocation(const ConfigLocation& location) { _locations.push_back(location); }
	bool	ConfigServer::addListen(std::string str)
	{
		if (str == "default_server")
		{
			if (_listens.empty())
				return (false);
			(_listens.back()).isDefault = true;
		}
		else
		{
			ListenTarget    newListen;
			std::size_t     colonPos = str.find(':');

			newListen.isDefault = false;
			if (colonPos != std::string::npos)
			{
				newListen.host = str.substr(0, colonPos);
				newListen.port = std::atoi(str.substr(colonPos + 1).c_str());
			}
			else
			{
				newListen.host = "0.0.0.0";
				newListen.port = std::atoi(str.c_str());
			}

			if (newListen.port <= 0 || newListen.port > 65535)
				return (false);

			_listens.push_back(newListen);
		}
		return (true);
	}


	// GETTER FUNCTIONS
	const std::string&	ConfigServer::getRoot() const { return _root; }
	const std::string&	ConfigServer::getHttpVersion() const { return _httpVersion; }
	const std::string&	ConfigServer::getSignature() const { return _signature; }
	std::size_t	ConfigServer::getMaxHeaderSize() const { return _maxHeaderSize; }
	std::size_t	ConfigServer::getMaxBodySize() const { return _maxBodySize; }
	/*
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
	*/

	const std::vector<std::string>& ConfigServer::getServerNames() const { return _serverNames; }
	const std::vector<ConfigLocation>& ConfigServer::getLocations() const { return _locations; }
	const std::vector<ListenTarget>& ConfigServer::getListens() const { return _listens; }

	
	void ConfigServer::print() const
    {
        std::cout << "=================== CONFIG SERVER ===================\n";
        std::cout << "Listens:            [";
		for (size_t i = 0; i < this->_listens.size(); ++i)
		{
			std::cout << this->_listens[i].host << ":";
			std::cout << this->_listens[i].port;
			if (this->_listens[i].isDefault)
				std::cout << "(default)";
			if (i + 1 < this->_listens.size())
				std::cout << ", ";
		}
		std::cout << "]\n";
        std::cout << "HTTP Version:       " << this->_httpVersion << "\n";
        std::cout << "Signature:          " << this->_signature << "\n";
        std::cout << "Root:               " << this->_root << "\n";
        std::cout << "Max Header Size:    " << this->_maxHeaderSize << " bytes\n";
        std::cout << "Max Body Size:      " << this->_maxBodySize << " bytes\n";
        
        std::cout << "Server Names:       [";
        for (size_t i = 0; i < this->_serverNames.size(); ++i)
        {
            std::cout << this->_serverNames[i];
            if (i + 1 < this->_serverNames.size())
                std::cout << ", ";
        }
        std::cout << "]\n";

        std::cout << "Locations Count:    " << this->_locations.size() << "\n";
        for (size_t i = 0; i < this->_locations.size(); ++i)
        {
            std::cout << "  Location #" << i + 1 << ":\n";
            this->_locations[i].print();
        }
        std::cout << "=====================================================\n" << std::endl;
    }
}