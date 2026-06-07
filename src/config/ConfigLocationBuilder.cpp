/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigLocationBuilder.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:06:16 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/07 16:56:02 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/config/ConfigLocationBuilder.hpp"
#include "../../include/config/ConfigLocation.hpp"

namespace config
{
	ConfigLocationBuilder::ConfigLocationBuilder() :
		_executePath(""),
		_rootPath(""),
		_uploadPath("/tmp"),
		_returnRedirection(std::make_pair(0, "/")),
		_autoIndex(false),
		_hasRedirection(false)
	{}

	ConfigLocationBuilder& ConfigLocationBuilder::setExecutePath(const std::string& executePath)
		{ _executePath = executePath; return (*this); }
	ConfigLocationBuilder& ConfigLocationBuilder::setRootPath(const std::string& rootPath)
		{ _rootPath = rootPath; return (*this); }
	ConfigLocationBuilder& ConfigLocationBuilder::setUploadPath(const std::string& uploadPath)
		{ _uploadPath = uploadPath; return (*this); }

	ConfigLocationBuilder& ConfigLocationBuilder::setReturnRedirection(int code, const std::string& url)
	{
		if (_hasRedirection)	
			throw std::invalid_argument("Invalid redirection usage: more than 1 redirection cannot be set");
		if (code < 300 || code > 399)
        	throw std::invalid_argument("Invalid redirection code: must be between 300 and 399");
		_returnRedirection = std::make_pair(code, url);
		_hasRedirection = true;
		return (*this);
	}

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
	
	ConfigLocationBuilder&	ConfigLocationBuilder::addCgiPass(const std::string& ext, const std::string& path)
	{
			if (_cgiPass.find(ext) != _cgiPass.end())
			throw std::runtime_error("Duplicate cgi_pass extension in config file: " + ext);
		_cgiPass[ext] = path;
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

	ConfigLocationBuilder&	ConfigLocationBuilder::addToIndexList(const std::string& path)
	{
		_indexList.push_back(path);
		return (*this);
	}

	ConfigLocation	ConfigLocationBuilder::build(void)
	{
		if (_executePath.empty())
			throw std::runtime_error("Location block missing execute path");
		if (_allowedMethods.empty())
		{
			_allowedMethods.push_back("GET");
			_allowedMethods.push_back("POST");
			_allowedMethods.push_back("DELETE");
			_allowedMethods.push_back("HEAD");
			_allowedMethods.push_back("PUT");
			// ! DEBUGGING
			std::cerr << "### No allowed methods specified, automatically added all." << std::endl;
			// ! END OF DEBUGGING
		}
		return (ConfigLocation(*this));
	}
}
