/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigLocationBuilder.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:06:16 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/24 12:51:51 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/config/ConfigLocationBuilder.hpp"
#include "../../include/config/ConfigLocation.hpp"

namespace config
{
	ConfigLocationBuilder::ConfigLocationBuilder() :
		_executePath(""),
		_rootPath(""),
		_uploadPath("tmp"),
		_returnRedirection(std::make_pair(0, "/")),
		_autoIndex(false),
		_hasRedirection(false),
		_maxHeaderSize(0),
		_maxBodySize(0)
	{ }

	ConfigLocationBuilder& ConfigLocationBuilder::setExecutePath(const std::string& executePath) { _executePath = executePath; return (*this); }
	
	ConfigLocationBuilder& ConfigLocationBuilder::setRootPath(const std::string& rootPath) { _rootPath = rootPath; return (*this); }
	
	ConfigLocationBuilder& ConfigLocationBuilder::setUploadPath(const std::string& uploadPath) { _uploadPath = uploadPath; return (*this); }

	ConfigLocationBuilder& ConfigLocationBuilder::setReturnRedirection(int code, const std::string& url)
	{
		if (_hasRedirection)	
			throw std::invalid_argument("Invalid redirection usage: more than 1 redirection cannot be set");
		if (code < 301 || code > 308)
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

	ConfigLocationBuilder&	ConfigLocationBuilder::setMaxHeaderSize(const std::string& str) { _maxHeaderSize = util::parseByte(str); return (*this); }

	ConfigLocationBuilder&	ConfigLocationBuilder::setMaxBodySize(const std::string& str){ _maxBodySize = util::parseByte(str); return (*this); }

	ConfigLocation	ConfigLocationBuilder::build(void)
	{
		if (_executePath.empty())
			throw std::runtime_error("Location block missing execute path");
		//if (!util::isDirExist(_executePath))
		//	throw std::runtime_error("Location directory is invalid");
		//if (_maxHeaderSize < 1024 || _maxHeaderSize > 10485760)
		//	throw std::runtime_error("client_max_header_size must be between 1KB (1.024 bytes) and 10MB (10.485.760 bytes)");
		//if (_maxBodySize < 1024 || _maxBodySize > 2147483648)
		//	throw std::runtime_error("client_max_body_size must be between 1KB (1.024 bytes) and 2GB (2.147.483.648 bytes)");
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
