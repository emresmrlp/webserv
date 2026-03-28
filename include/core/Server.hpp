/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:36:01 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/28 10:35:19 by ysumeral         ###   ########.fr       */
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
			Server(const config::ConfigServer &config);
			~Server();
			const config::ConfigServer &getConfig() const;
		private:
			const config::ConfigServer &_config;
	};
}

#endif