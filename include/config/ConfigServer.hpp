/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:06:11 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/23 15:45:06 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGSERVER_HPP
# define CONFIGSERVER_HPP
# include <string>
# include <vector>
# include "ConfigLocation.hpp"

namespace config
{
	class ConfigServer
	{
		public:
			ConfigServer();
			~ConfigServer();

			void setPort(int port);
			void setHost(const std::string& host);
			void setServerNames(const std::vector<std::string>& serverNames);
			void setRoot(const std::string& root);
			void setLocations(const std::vector<ConfigLocation>& locations);	

			int getPort() const;
			const std::string& getHost() const;
			const std::vector<std::string>& getServerNames() const;
			const std::string& getRoot() const;
			const std::vector<ConfigLocation>& getLocations() const;
		private:
			int							_port;
			std::string					_host;
			std::vector<std::string>	_serverNames;
			std::string					_root;
			std::vector<ConfigLocation> _locations;
	};
}

#endif