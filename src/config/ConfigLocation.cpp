/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigLocation.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:23:04 by ysumeral          #+#    #+#             */
/*   Updated: 2026/05/19 15:08:56 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/config/ConfigLocation.hpp"
#include <iostream> // !delete

namespace config
{
	ConfigLocation::ConfigLocation()
		: _rootPath(""), _executePath(""), _returnRedirection(""), _autoIndex(false) { }

	ConfigLocation::~ConfigLocation() { }

	// SETTER FUNCTIONS
	bool ConfigLocation::setExecutePath(const std::string& executePath)
		{ _executePath = executePath; return (true); }
	bool ConfigLocation::setRootPath(const std::string& rootPath)
		{ _rootPath = rootPath; return (true); }
	bool ConfigLocation::setReturnRedirection(const std::string& returnRedirection)
		{ _returnRedirection = returnRedirection; return (true); }
	bool ConfigLocation::setAutoIndex(std::string str)
	{
		if (str == "on")
			_autoIndex = true;
		else if (str == "off")
			_autoIndex = false;
		else
			return (false);
		return (true);
	}
	
	bool	ConfigLocation::addAllowedMethod(const std::string& method)
	{
		if (method != "GET" && method != "POST" && method != "DELETE")
			return false;
		_allowedMethods.push_back(method);
		return true;
	}

	
	// GETTER FUNCTIONS
	const std::string& ConfigLocation::getExecutePath() const { return _executePath; }
	const std::string& ConfigLocation::getRootPath() const { return _rootPath; }
	const std::string& ConfigLocation::getReturnRedirection() const { return _returnRedirection; }
	bool ConfigLocation::getAutoIndex() const { return _autoIndex; }

	const std::vector<std::string>& ConfigLocation::getAllowedMethods() const { return _allowedMethods; }


	void ConfigLocation::print() const
    {
        std::cout << "      Execute Path:       " << this->_executePath << "\n";
        std::cout << "      Root Path:          " << this->_rootPath << "\n";
        std::cout << "      Return Redirection: " << this->_returnRedirection << "\n";
        std::cout << "      Auto Index:         " << (this->_autoIndex ? "on" : "off") << "\n";
        std::cout << "      Allowed Methods:    [";
        for (size_t i = 0; i < this->_allowedMethods.size(); ++i)
        {
            std::cout << this->_allowedMethods[i];
            if (i + 1 < this->_allowedMethods.size())
                std::cout << ", ";
        }
        std::cout << "]\n";
    }
}