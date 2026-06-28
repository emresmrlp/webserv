/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseDispatcher.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 12:25:40 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/29 01:46:09 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSEDISPATCHER_HPP
# define RESPONSEDISPATCHER_HPP
# include <map>
# include <string>

namespace config
{
	class ConfigServer;
}

namespace http
{
	class IMethodHandler;
	class IResponse;
	class Request;
	class ResponseFactory;

	class ResponseDispatcher
	{
		public:
			ResponseDispatcher(ResponseFactory &factory);
			~ResponseDispatcher();
			http::IResponse *dispatch(const config::ConfigServer *_config, http::Request *request);
		private:
			ResponseFactory									&_factory;
			std::map<std::string, http::IMethodHandler *>	_handlers;
	};
}

#endif