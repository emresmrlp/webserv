/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Util.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 14:41:15 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/14 10:51:29 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Util.hpp"
#include <sys/stat.h>
#include <stdexcept>
#include <sstream>

namespace util
{
	void toLowerCase(std::string &str)
	{
		for (std::size_t i = 0; i < str.length(); ++i)
			str[i] = std::tolower(static_cast<unsigned char>(str[i]));
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