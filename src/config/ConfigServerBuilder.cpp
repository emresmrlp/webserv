/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServerBuilder.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:06:16 by ysumeral          #+#    #+#             */
/*   Updated: 2026/05/19 16:54:57 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/config/ConfigServerBuilder.hpp"
#include "../../include/config/ConfigServer.hpp"

namespace config
{
	ConfigServerBuilder::ConfigServerBuilder()	:
		_root("/"),
		_httpVersion("HTTP/1.1"),
		_signature("YECS-BME ADI ORTAKLIGI"),
		_maxHeaderSize(1048576),
		_maxBodySize(1048576)
	{ }

	size_t ConfigServerBuilder::parseByte(std::string str) const
	{
		if (str.empty())
			return 1024 * 1024;

		char unit = std::toupper(str[str.length() - 1]);
		size_t multiplier = 1;

		if (unit == 'K') multiplier = 1024;
		else if (unit == 'M') multiplier = 1024 * 1024;
		else if (unit == 'G') multiplier = 1024 * 1024 * 1024;
		else if (!std::isdigit(unit)) 
			throw std::invalid_argument("Invalid byte format: unknown unit");
			
		if (unit == 'K' || unit == 'M' || unit == 'G') 
			str.resize(str.length() - 1);

		if (str.empty())
			throw std::invalid_argument("Invalid byte format: no number provided");

		for (size_t i = 0; i < str.length(); ++i)
			if (!std::isdigit(str[i]))
				throw std::invalid_argument("Invalid byte format: non-numeric characters found");

		size_t num = std::strtoul(str.c_str(), NULL, 10);

		if (num == 0)
			return 1024 * 1024;

		return num * multiplier;
	}

	ConfigServerBuilder&	ConfigServerBuilder::setRoot(const std::string& root) {
		_root = root; return (*this);
	}

	//ConfigServerBuilder&	ConfigServerBuilder::setHttpVersion(const std::string& version) { _httpVersion = version; }

	//ConfigServerBuilder&	ConfigServerBuilder::setSignature(const std::string& signature) { _signature = signature; }

	ConfigServerBuilder&	ConfigServerBuilder::setMaxHeaderSize(const std::string& str) {
		_maxHeaderSize = parseByte(str);
		return (*this);
	}

	ConfigServerBuilder&	ConfigServerBuilder::setMaxBodySize(const std::string& str){
		_maxBodySize = parseByte(str);
		return (*this);
	}

	ConfigServerBuilder&	ConfigServerBuilder::addServerName(const std::string& serverName) {
		if (std::find(_serverNames.begin(), _serverNames.end(), serverName) != _serverNames.end())
			throw std::invalid_argument("Invalid server_name: can't put the same server_name twice");
		_serverNames.push_back(serverName);
		return (*this);
	}

	ConfigServerBuilder&	ConfigServerBuilder::addLocation(const ConfigLocation& location) {
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
		if (_listens.empty())
		{
			addListen("0.0.0.0:8080");
			std::cerr << "# listen cannot be empty, automatically added 0.0.0.0:8080" << std::endl;
		}
		if (_serverNames.empty())
		{
			addServerName("");
			std::cerr << "# server_names cannot be empty, automatically added \"\"" << std::endl;
		}
		if (_locations.empty())
			throw std::runtime_error("No location found for a server");
		if (_root.empty())
			throw std::runtime_error("Server root directory cannot be empty");
		return (ConfigServer(*this));
	}
}
