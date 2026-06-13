/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:58:22 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/13 18:54:04 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETHANDLER_HPP
# define GETHANDLER_HPP
# include "IMethodHandler.hpp"

namespace http
{
	class IResponse;
	class ResponseFactory;

	class GetHandler : public http::IMethodHandler
	{
		public:
			GetHandler(ResponseFactory &factory);
			~GetHandler();
			virtual http::IResponse *handle(const config::ConfigServer *config, 
				const config::ConfigLocation *configLoc, http::Request *request) const;
		private:
			ResponseFactory &_factory;
	};
}

#endif