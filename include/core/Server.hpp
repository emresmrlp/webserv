/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:36:01 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/23 16:18:04 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP
# include "ConfigServer.hpp"

namespace core
{
	class Server
	{
		public:
			Server();
			~Server();
			void init();
			config::ConfigServer &getConfig();
		private:
			config::ConfigServer *_config;
	};
}

#endif