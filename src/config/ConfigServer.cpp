/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:06:16 by ysumeral          #+#    #+#             */
/*   Updated: 2026/05/19 16:54:57 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/config/ConfigServer.hpp"
#include "../../include/config/ConfigServerBuilder.hpp"
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
	
	const std::string&	ConfigServer::getRoot() const { return _root; }
	const std::string&	ConfigServer::getHttpVersion() const { return _httpVersion; }
	const std::string&	ConfigServer::getSignature() const { return _signature; }
	const long&			ConfigServer::getMaxHeaderSize() const { return _maxHeaderSize; }
	const long&			ConfigServer::getMaxBodySize() const { return _maxBodySize; }
	const std::string&	ConfigServer::getErrorPage(int number) const { return _errorPages.find(number)->second; }

	const std::vector<std::string>& ConfigServer::getServerNames() const { return _serverNames; }
	const std::vector<ConfigLocation>& ConfigServer::getLocations() const { return _locations; }
	const std::vector<ListenTarget>& ConfigServer::getListens() const { return _listens; }
	const std::map<int, std::string>& ConfigServer::getErrorPages() const { return _errorPages; }

	
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
