/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseDispatcher.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 12:25:40 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/13 09:45:27 by ysumeral         ###   ########.fr       */
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
			ResponseDispatcher(ResponseFactory &factory);
			~ResponseDispatcher();
			http::IResponse *dispatch(const config::ConfigServer *_config, http::Request *request);
		private:
			ResponseFactory				&_factory;
	};
}

#endif