/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseDispatcher.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 12:25:40 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/28 10:37:40 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSEDISPATCHER_HPP
# define RESPONSEDISPATCHER_HPP
# include "Server.hpp"
# include "Request.hpp"
# include "IResponse.hpp"
# include "ResponseFactory.hpp"

namespace http
{
	class ResponseDispatcher
	{
		public:
			ResponseDispatcher(const config::ConfigServer &config, ResponseFactory &factory);
			~ResponseDispatcher();
			http::IResponse *dispatch(http::Request &request);
		private:
			const config::ConfigServer	&_config;
			ResponseFactory				&_factory;
	};
}

#endif