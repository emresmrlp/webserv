/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigLocationBuilder.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:06:16 by ysumeral          #+#    #+#             */
/*   Updated: 2026/05/19 16:54:57 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/config/ConfigLocationBuilder.hpp"
#include "../../include/config/ConfigLocation.hpp"

namespace config
{
	ConfigLocationBuilder::ConfigLocationBuilder() :
		_executePath(""),
		_rootPath(""),
		_returnRedirection(""),
		_autoIndex(false)
	{}

	ConfigLocationBuilder& ConfigLocationBuilder::setExecutePath(const std::string& executePath)
		{ _executePath = executePath; return (*this); }
	ConfigLocationBuilder& ConfigLocationBuilder::setRootPath(const std::string& rootPath)
		{ _rootPath = rootPath; return (*this); }
	ConfigLocationBuilder& ConfigLocationBuilder::setReturnRedirection(const std::string& returnRedirection)
		{ _returnRedirection = returnRedirection; return (*this); }

	ConfigLocationBuilder& ConfigLocationBuilder::setAutoIndex(const std::string& str)
	{
		if (str == "on")
			_autoIndex = true;
		else if (str == "off")
			_autoIndex = false;
		else
			throw std::invalid_argument("Invalid autoindex value: must be 'on' or 'off'");
		return (*this);
	}
	
	ConfigLocationBuilder&	ConfigLocationBuilder::addAllowedMethod(const std::string& method)
	{
		if (method != "GET" && method != "POST" && method != "DELETE")
			throw std::invalid_argument("Invalid allowed_method: must be GET, POST or DELETE");
		if (std::find(_allowedMethods.begin(), _allowedMethods.end(), method) != _allowedMethods.end())
			throw std::invalid_argument("Invalid allowed_method input: methods must only appear once");
		_allowedMethods.push_back(method);
		return (*this);
	}

	ConfigLocation	ConfigLocationBuilder::build(void)
	{
		if (_executePath.empty())
			throw std::runtime_error("Location block missing execute path");
		if (_allowedMethods.empty())
		{
			_allowedMethods.push_back("GET");
			std::cerr << "### Allowed methods for the location was empty, automatically added 'GET'" << std::endl;
		}
		return (ConfigLocation(*this));
	}
}
