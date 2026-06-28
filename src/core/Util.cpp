/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Util.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 14:41:15 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/28 09:37:57 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Util.hpp"
#include <sys/stat.h>
#include <stdexcept>
#include <sstream>
#include <ctime>
#include <cstdlib>

namespace util
{
	void toUpperCaseSnake(std::string &str)
	{
		for (std::size_t i = 0; i < str.length(); ++i)
		{
			if (str[i] == '-')
				str[i] = '_';
			else
				str[i] = std::tolower(static_cast<unsigned char>(str[i]));
		}
	}

	void toLowerCase(std::string &str)
	{
		for (std::size_t i = 0; i < str.length(); ++i)
			str[i] = std::toupper(static_cast<unsigned char>(str[i]));
	}

	std::string getCurrentDate()
	{
		char	buffer[50];
		time_t	timestamp;
		
		timestamp = time(NULL);
		std::strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", localtime(&timestamp));
		return (buffer);
	}

	std::string getCurrentTimestamp()
	{
		char	buffer[50];
		time_t	timestamp;
		
		timestamp = time(NULL);
		std::strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", localtime(&timestamp));
		return (buffer);
	}

	std::string	toString(std::size_t size)
	{
		std::ostringstream oss;

		oss << size;
		return (oss.str());
	}

	bool isFileExist(const std::string &path)
	{
		struct stat st;
		if (stat(path.c_str(), &st) == 0)
			return (S_ISREG(st.st_mode));
		return (false);
	}

	bool isDirExist(const std::string &path)
	{
		struct stat st;
		if (stat(path.c_str(), &st) == 0)
			return (S_ISDIR(st.st_mode));
		return (false);
	}

	std::string getRelativeConfigPath(const config::ConfigServer *config, const config::ConfigLocation *configLoc)
	{
		if (configLoc == NULL || configLoc->getRootPath().empty())
			return (config->getRoot());
		return (configLoc->getRootPath());
	}

	const std::string getExtension(const std::string &path)
	{
		std::size_t	dotPos;
		std::size_t	queryPos;
		std::string	literalPath;

		queryPos = path.find_first_of("?");
		if (queryPos == std::string::npos)
			literalPath = path;
		else
			literalPath = path.substr(0, queryPos);

		dotPos = literalPath.find_last_of(".");
		if (dotPos == std::string::npos)
			return (std::string(""));
		return (literalPath.substr(dotPos));
	}

	const std::string getFixedRoute(const std::string &route)
	{
		std::string fixedRoute = route;
		if (fixedRoute.empty())
			return (fixedRoute);
		std::size_t pos;
		while (fixedRoute.find("//") != std::string::npos)
		{
			pos = fixedRoute.find("//");
			fixedRoute.replace(pos, 2, "/");
		}
		return (fixedRoute);
	}

	const std::string getMimeType(const std::string &path)
    {
        std::string contentType;
        std::string extension;

        extension = util::getExtension(path);
		if (extension == "")
			return "application/octet-stream";

        static std::map<std::string, std::string> mimeTypes;
		if (mimeTypes.empty())
		{
			mimeTypes[".html"]  = "text/html";
			mimeTypes[".htm"]   = "text/html";
			mimeTypes[".css"]   = "text/css";
			mimeTypes[".js"]    = "application/javascript";
			mimeTypes[".mjs"]   = "text/javascript";
			mimeTypes[".json"]  = "application/json";
			mimeTypes[".xml"]   = "application/xml";
			mimeTypes[".txt"]   = "text/plain";
			mimeTypes[".csv"]   = "text/csv";
			mimeTypes[".md"]    = "text/markdown";
			mimeTypes[".yaml"]  = "text/yaml";
			mimeTypes[".yml"]   = "text/yaml";
			mimeTypes[".png"]   = "image/png";
			mimeTypes[".jpg"]   = "image/jpeg";
			mimeTypes[".jpeg"]  = "image/jpeg";
			mimeTypes[".gif"]   = "image/gif";
			mimeTypes[".webp"]  = "image/webp";
			mimeTypes[".svg"]   = "image/svg+xml";
			mimeTypes[".ico"]   = "image/x-icon";
			mimeTypes[".mp3"]   = "audio/mpeg";
			mimeTypes[".mp4"]   = "video/mp4";
			mimeTypes[".pdf"]   = "application/pdf";
			mimeTypes[".zip"]   = "application/zip";
			mimeTypes[".rar"]   = "application/vnd.rar";
			mimeTypes[".tar"]   = "application/x-tar";
		}
        std::map<std::string, std::string>::const_iterator it;
        for (it = mimeTypes.begin(); it != mimeTypes.end(); ++it)
        {
            if (it->first == extension)
                return (mimeTypes[extension]);
        }
        return "application/octet-stream";
    }

	size_t	parseByte(std::string str)
	{
		if (str.empty())
			return 1024 * 1024;

		char	unit = std::toupper(str[str.length() - 1]);
		size_t	multiplier = 1;

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
}