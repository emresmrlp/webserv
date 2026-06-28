/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IResponse.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 12:26:56 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/29 00:28:32 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRESPONSE_HPP
# define IRESPONSE_HPP
# include <string>

namespace http
{
	class IResponse
	{
		public:
			virtual ~IResponse() {};
			virtual std::string serialize() const = 0;
			virtual void clearBody() = 0;
	};
}

#endif