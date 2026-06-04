/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:36:01 by ysumeral          #+#    #+#             */
/*   Updated: 2026/05/31 15:32:26 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP
# include <unistd.h>
# include <iostream>
# include <netdb.h>
# include <sstream>
# include <cstring>
# include "Types.hpp"
# include "ConfigServer.hpp"

namespace core
{
	class Server
	{
		public:
			Server(const config::ConfigServer &config, const HostAddr &addr);
			~Server();

			void						setup();
			int							getListenFd() const;
			const HostAddr				&getAddr() const;
			const config::ConfigServer	&getConfig() const;
		private:
			Server(const Server&);
			Server& operator=(const Server&);

			int 						_listenFd;
			const HostAddr				_addr;
			const config::ConfigServer	&_config;
	};
}

#endif