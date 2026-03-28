/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:36:02 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/28 10:45:29 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERHANDLER_HPP
# define SERVERHANDLER_HPP
# include "Server.hpp"
# include "Connection.hpp"

namespace core
{
	class ServerHandler
	{
		public:
			ServerHandler();
			~ServerHandler();
			void createServer(config::ConfigServer &server_one, config::ConfigServer &server_two);
			const std::vector<core::Server>& getServers() const;
		private:
			std::vector<Server> _servers;
			std::vector<std::pair<int, Connection> > _connnections;
	};
}

#endif