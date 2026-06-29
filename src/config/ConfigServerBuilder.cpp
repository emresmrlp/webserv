/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServerBuilder.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:06:16 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/29 11:31:19 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigServerBuilder.hpp"
#include "ConfigServer.hpp"
#include "ConfigLocation.hpp"
#include "Util.hpp"
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <stdexcept>

namespace config
{
	ConfigServerBuilder::ConfigServerBuilder()	:
		_root(""),
		_httpVersion("HTTP/1.1"),
		_signature("YECS-BME ADI ORTAKLIGI"),
		_maxHeaderSize(8192),
		_maxBodySize(314572800)
	{ }

	ConfigServerBuilder&	ConfigServerBuilder::setRoot(const std::string& root) { _root = root; return (*this); }

	ConfigServerBuilder&	ConfigServerBuilder::setHttpVersion(const std::string& version) { _httpVersion = version; return (*this); }

	ConfigServerBuilder&	ConfigServerBuilder::setMaxHeaderSize(const std::string& str) { _maxHeaderSize = util::parseByte(str); return (*this); }

	ConfigServerBuilder&	ConfigServerBuilder::setMaxBodySize(const std::string& str){ _maxBodySize = util::parseByte(str); return (*this); }

	ConfigServerBuilder&	ConfigServerBuilder::addServerName(const std::string& serverName)
	{
		if (std::find(_serverNames.begin(), _serverNames.end(), serverName) != _serverNames.end())
			throw std::invalid_argument("Invalid server_name: can't put the same server_name twice");
		_serverNames.push_back(serverName);
		return (*this);
	}

	ConfigServerBuilder&	ConfigServerBuilder::addLocation(const ConfigLocation& location)
	{
		for (size_t i = 0; i < _locations.size(); ++i)
		{
			if (_locations[i].getExecutePath() == location.getExecutePath())
				throw std::invalid_argument("Duplicate location path: " + location.getExecutePath());
		}
		_locations.push_back(location);
		return *this;
	}

	ConfigServerBuilder&	ConfigServerBuilder::addListen(const std::string& str)
	{
		if (str == "default_server")
		{
			if (_listens.empty())
				throw std::invalid_argument("Invalid default_server use: must put a port before making it default");
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
				throw std::invalid_argument("Invalid host port pair");

			_listens.push_back(newListen);
		}
		return (*this);
	}
	
	ConfigServerBuilder&	ConfigServerBuilder::addErrorPage(const std::string& no, const std::string& loc)
	{
		int	errorNo = std::atoi(no.c_str());
		if ((errorNo >= 400 && errorNo <= 417) ||
			(errorNo >= 500 && errorNo <= 504))
			_errorPages[errorNo] = loc;
		else
		{
			std::ostringstream oss;
			oss << "Invalid error page: can't declare a error page for " << errorNo;
			throw std::invalid_argument(oss.str());
		}
		return (*this);
	}
	
	ConfigServer	ConfigServerBuilder::build(void)
	{
		if (_root.empty())
			throw std::runtime_error("Root must be set for each server");
		if (!util::isDirExist(_root))
			throw std::runtime_error("Root directory is invalid");
		if (_maxHeaderSize > 8192)
		{
			std::ostringstream	ss;
			ss << "client_max_header_size must be between 1 byte and 8KB (8.192 bytes): " << _maxHeaderSize;
			throw std::runtime_error(ss.str());
		}
		if (_maxBodySize > 314572800)
		{
			std::ostringstream	ss;
			ss << "client_max_body_size must be between 1 byte and 300MB (314.572.800 bytes): " << _maxBodySize;
			throw std::runtime_error(ss.str());
		}
		if (_listens.empty())
			addListen("0.0.0.0:8080");
		if (_serverNames.empty())
			addServerName("");
		if (_locations.empty())
			throw std::runtime_error("No location found for the server");
		return (ConfigServer(*this));
	}
}
