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
#include "../../include/config/ConfigLocationBuilder.hpp"
#include <iostream> // !delete

namespace config
{
	ConfigLocation::ConfigLocation(const ConfigLocationBuilder& builder) :
		_executePath(builder._executePath),
		_rootPath(builder._rootPath),
		_returnRedirection(builder._returnRedirection),
		_allowedMethods(builder._allowedMethods),
		_autoIndex(builder._autoIndex)
	{ }

	const std::string&	ConfigLocation::getExecutePath() const { return _executePath; }
	const std::string&	ConfigLocation::getRootPath() const { return _rootPath; }
	const std::string&	ConfigLocation::getReturnRedirection() const { return _returnRedirection; }
	bool				ConfigLocation::getAutoIndex() const { return _autoIndex; }

	const std::vector<std::string>&	ConfigLocation::getAllowedMethods() const { return _allowedMethods; }

	void ConfigLocation::print() const
	{
		std::cout << "      Execute Path:       " << this->_executePath << "\n";
		std::cout << "      Root Path:          " << this->_rootPath << "\n";
		std::cout << "      Return Redirection: " << this->_returnRedirection << "\n";
		std::cout << "      Auto Index:         " << (this->_autoIndex ? "on" : "off") << "\n";
		std::cout << "      Allowed Methods:    [";
		for (size_t i = 0; i < this->_allowedMethods.size(); i++)
		{
			std::cout << this->_allowedMethods[i];
			if (i + 1 < this->_allowedMethods.size())
				std::cout << ", ";
		}
		std::cout << "]\n";
	}
}