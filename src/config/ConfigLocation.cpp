/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigLocation.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:23:04 by ysumeral          #+#    #+#             */
/*   Updated: 2026/05/03 18:19:27 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigLocation.hpp"

namespace config
{
	ConfigLocation::ConfigLocation()
		: _rootPath(""), _executePath(""), _returnRedirection(""), _autoIndex(false)
	{}

	ConfigLocation::~ConfigLocation() {}

	const std::string& ConfigLocation::getRootPath() const {
		return _rootPath;
	}

	const std::string& ConfigLocation::getExecutePath() const {
		return _executePath;
	}

	const std::string& ConfigLocation::getReturnRedirection() const {
		return _returnRedirection;
	}

	const std::vector<std::string>& ConfigLocation::getAllowedMethods() const {
		return _allowedMethods;
	}

	bool ConfigLocation::getAutoIndex() const {
		return _autoIndex;
	}

	void ConfigLocation::setRootPath(const std::string& rootPath) {
		_rootPath = rootPath;
	}

	void ConfigLocation::setExecutePath(const std::string& executePath) {
		_executePath = executePath;
	}

	void ConfigLocation::setReturnRedirection(const std::string& returnRedirection) {
		_returnRedirection = returnRedirection;
	}

	void	ConfigLocation::addAllowedMethod(const std::string& allowedMethod)
	{
		_allowedMethods.push_back(allowedMethod);
	}

	/*void ConfigLocation::setAllowedMethods(const std::vector<std::string>& allowedMethods) {
		_allowedMethods = allowedMethods;
	}*/

	void ConfigLocation::setAutoIndex(bool autoIndex) {
		_autoIndex = autoIndex;
	}
}