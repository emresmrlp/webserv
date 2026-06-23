/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Util.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 14:40:45 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/23 04:34:12 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_HPP
# define UTIL_HPP
# include <string>
# define CRLF "\r\n"
# define DOUBLE_CRLF "\r\n\r\n"
#include "ConfigServer.hpp"
#include "ConfigLocation.hpp"

namespace util
{
	std::string	toString(std::size_t size);
	void		toLowerCase(std::string &str);
	bool		isFileExist(const std::string &path);
	bool		isDirExist(const std::string &path);
	size_t		parseByte(std::string str);
	std::string getRelativeConfigPath(const config::ConfigServer *config, const config::ConfigLocation *configLoc);
	std::string	getCurrentDate();
	std::string	getCurrentTimestamp();
}

#endif