/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Util.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 14:41:15 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/22 17:58:13 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Util.hpp"

namespace util
{
	void toLowerCase(std::string &str)
	{
		for (std::size_t i = 0; i < str.length(); ++i)
			str[i] = std::tolower(static_cast<unsigned char>(str[i]));
	}
}