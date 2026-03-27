/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:36:02 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/27 16:06:53 by ysumeral         ###   ########.fr       */
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
			void createServer();
		private:
			std::vector<Server> _servers;
			std::vector<std::pair<int, Connection> > _connnections;
	};
}

#endif