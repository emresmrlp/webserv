/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:36:02 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/16 11:51:33 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERHANDLER_HPP
# define SERVERHANDLER_HPP
# include "Server.hpp"
# include "Connection.hpp"
# include <poll.h>
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

			static bool					_running;
			std::vector<Server *>		_servers;
			std::vector<Connection *>	_connnections;
			std::vector<struct pollfd>	_pollFds;

			static void	signalHandler(int sig);
			void		acceptConnection(std::size_t i);
			void		closeConnection(std::size_t i);
			void		readConnection(std::size_t i);
			void		writeConnection(std::size_t i);
			void		dispatch(std::size_t i);
			bool		isActiveServer(HostAddr &addr);
			HostAddr	resolveHostAddr(const std::string &ip, int port);
	};
}

#endif