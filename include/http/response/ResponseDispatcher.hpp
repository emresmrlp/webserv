/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseDispatcher.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 12:25:40 by ysumeral          #+#    #+#             */
/*   Updated: 2026/05/31 21:06:17 by ysumeral         ###   ########.fr       */
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
			http::IResponse *dispatch(http::Request *request, const config::ConfigServer *_config);
		private:
			ResponseFactory				&_factory;
	};
}

#endif