/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:36:02 by ysumeral          #+#    #+#             */
/*   Updated: 2026/05/31 15:30:41 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERHANDLER_HPP
# define SERVERHANDLER_HPP
# include "Server.hpp"
# include "Connection.hpp"
# include <exception>

namespace core
{	
	class ServerHandler
	{
		public:
			ServerHandler();
			~ServerHandler();
			
			void init(const std::vector<config::ConfigServer> &_configs); // ? creates Server objects from ConfigServer vector
    		void run();
		private:
			ServerHandler(const ServerHandler&);
			ServerHandler& operator=(const ServerHandler&);

			std::vector<Server *>						_servers;
			std::vector<std::map<int, Connection *> >	_connnections;
			std::vector<struct pollfd>					_pollfds;

			bool		isActiveServer(HostAddr &addr);
			HostAddr	resolveHostAddr(const std::string &ip, int port);
	};
}

#endif