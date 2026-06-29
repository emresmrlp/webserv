/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigLocation.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:23:04 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/29 11:20:21 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigLocation.hpp"
#include "ConfigLocationBuilder.hpp"
#include <algorithm>

namespace config
{
	ConfigLocation::ConfigLocation(const ConfigLocationBuilder& builder) :
		_executePath(builder._executePath),
		_rootPath(builder._rootPath),
		_uploadPath(builder._uploadPath),
		_returnRedirection(builder._returnRedirection),
		_cgiPass(builder._cgiPass),
		_allowedMethods(builder._allowedMethods),
		_indexList(builder._indexList),
		_autoIndex(builder._autoIndex),
		_hasRedirection(builder._hasRedirection),
		_maxHeaderSize(builder._maxHeaderSize),
		_maxBodySize(builder._maxBodySize)
	{ }

	const std::string&			ConfigLocation::getExecutePath() const { return _executePath; }
	
	const std::string&			ConfigLocation::getRootPath() const { return _rootPath; }
	
	const std::string&			ConfigLocation::getUploadPath() const { return _uploadPath; }
	
	std::pair<int, std::string>	ConfigLocation::getReturnRedirection() const { return _returnRedirection; }

	const std::string&			ConfigLocation::getCgiPass(const std::string& ext) const
	{
		std::map<std::string, std::string>::const_iterator it = _cgiPass.find(ext);

		if (it != _cgiPass.end())
			return it->second;
		static const std::string emptyString = "";
		return emptyString;
	}

	const std::vector<std::string>&	ConfigLocation::getAllowedMethods() const { return _allowedMethods; }

	const std::vector<std::string>&	ConfigLocation::getIndexList() const { return _indexList; }
	
	bool	ConfigLocation::isAllowed(const std::string& method) const 
	{
		for (size_t i = 0; i < _allowedMethods.size(); i++)
			if (_allowedMethods[i] == method)
				return (true);
		return (false);
	}

	bool			ConfigLocation::getAutoIndex() const { return _autoIndex; }

	bool			ConfigLocation::hasRedirection() const { return _hasRedirection; }

	std::size_t 			ConfigLocation::getMaxHeaderSize() const { return _maxHeaderSize; }
	
	std::size_t 			ConfigLocation::getMaxBodySize() const { return _maxBodySize; }
}
