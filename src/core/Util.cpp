/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Util.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 14:41:15 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/27 11:27:27 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Util.hpp"
#include <sys/stat.h>

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
}