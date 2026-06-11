/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Util.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 14:40:45 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/07 18:04:41 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_HPP
# define UTIL_HPP
# include <string>
# define CRLF "\r\n"
# define DOUBLE_CRLF "\r\n\r\n"

namespace util
{	
	void	toLowerCase(std::string &str);
	bool	isFileExist(const std::string &path);
	bool	isDirExist(const std::string &path);
	size_t	parseByte(std::string str);
}

#endif