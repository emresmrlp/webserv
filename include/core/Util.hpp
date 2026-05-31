/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Util.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 14:40:45 by ysumeral          #+#    #+#             */
/*   Updated: 2026/05/31 14:03:56 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_HPP
# define UTIL_HPP
# include <string>
# define CRLF "\r\n"
# define DOUBLE_CRLF "\r\n\r\n"

namespace util
{	
	void toLowerCase(std::string &str);
	bool isFileExist(const std::string &path);
}

#endif