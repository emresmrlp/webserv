/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:06:16 by ysumeral          #+#    #+#             */
/*   Updated: 2026/05/26 18:25:47 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigServer.hpp"
#include "ConfigServerBuilder.hpp"
#include "ConfigLocation.hpp"
#include <iostream> // !delete

namespace config
{
	ConfigServer::ConfigServer(const ConfigServerBuilder& builder) :
		_root(builder._root),
		_httpVersion(builder._httpVersion),
		_signature(builder._signature),
		_maxHeaderSize(builder._maxHeaderSize),
		_maxBodySize(builder._maxBodySize),
		_serverNames(builder._serverNames),
		_locations(builder._locations),
		_listens(builder._listens),
		_errorPages(builder._errorPages)
	{ }
	
	const std::string&		ConfigServer::getRoot()					const { return _root; }
	
	const std::string&		ConfigServer::getHttpVersion()			const { return _httpVersion; }
	
	const std::string&		ConfigServer::getSignature()			const { return _signature; }
	
	std::size_t 			ConfigServer::getMaxHeaderSize()		const { return _maxHeaderSize; }
	
	std::size_t 			ConfigServer::getMaxBodySize()			const { return _maxBodySize; }
	
	const std::string&		ConfigServer::getErrorPage(int number)	const
	{
		std::map<int, std::string>::const_iterator it = _errorPages.find(number);
	
		if (it != _errorPages.end())
			return it->second;
			
		static const std::string emptyString = "";
		return emptyString;
	}
	
	const std::vector<std::string>&		ConfigServer::getServerNames() const { return _serverNames; }
	
	const std::vector<ConfigLocation>&	ConfigServer::getLocations() const { return _locations; }
	
	const std::vector<ListenTarget>&	ConfigServer::getListens() const { return _listens; }
	
	const std::map<int, std::string>&	ConfigServer::getErrorPages() const { return _errorPages; }

	const ConfigLocation*				ConfigServer::getLocation(const std::string& str) const
	{
		const ConfigLocation* bestMatch = NULL;
		size_t longestMatch = 0;

		for (size_t i = 0; i < _locations.size(); ++i)
		{
			std::string locPath = _locations[i].getExecutePath();
			
			if (str.find(locPath) == 0)
			{
				if (locPath.length() > longestMatch)
				{
					longestMatch = locPath.length();
					bestMatch = &_locations[i];
				}
			}
		}
		
		return bestMatch;
	}
	
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
		for (std::map<int, std::string>::const_iterator it = _errorPages.begin(); it != _errorPages.end(); ++it) {
			std::cout << "Error Page " << it->first << ":     " << it->second << std::endl;
		}
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
