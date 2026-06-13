/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMethodHandler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 12:26:56 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/13 18:28:07 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMETHODHANDLER_HPP
# define IMETHODHANDLER_HPP
# include "ConfigServer.hpp"
# include "ConfigLocation.hpp"
# include "Request.hpp"

namespace http
{
	class IResponse;
    class ResponseFactory;
	
	class IMethodHandler
	{
		public:
			virtual ~IMethodHandler() {};
			virtual IResponse *handle(const config::ConfigServer *config, const config::ConfigLocation *configLoc, http::Request *request) const = 0;
	};
}

#endif