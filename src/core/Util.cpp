/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Util.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 14:41:15 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/07 18:03:45 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Util.hpp"
#include <sys/stat.h>
#include <stdexcept>

namespace util
{
	void toLowerCase(std::string &str)
	{
		for (std::size_t i = 0; i < str.length(); ++i)
			str[i] = std::tolower(static_cast<unsigned char>(str[i]));
	}

	bool isFileExist(const std::string &path)
	{
		struct stat st;
		if (stat(path.c_str(), &st) == 0) // file exist?
			return (S_ISREG(st.st_mode)); // is that directory?
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