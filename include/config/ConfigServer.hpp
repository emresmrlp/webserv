/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:06:11 by ysumeral          #+#    #+#             */
/*   Updated: 2026/05/03 18:07:30 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGSERVER_HPP
# define CONFIGSERVER_HPP
# include <string>
# include <vector>
# include <exception>
# include "ConfigLocation.hpp"

namespace config
{
	class ConfigServer
	{
		public:
			ConfigServer();
			~ConfigServer();

			void	setPort(int port);
			void	setHost(const std::string& host);
			void	addServerName(const std::string& serverName);
			//void	setServerNames(const std::vector<std::string>& serverNames);
			void	setRoot(const std::string& root);
			void	addLocation(const ConfigLocation& location);
			//void	setLocations(const std::vector<ConfigLocation>& locations);

			int getPort() const;
			const std::string&					getHost() const;
			const std::vector<std::string>&		getServerNames() const;
			const std::string&					getRoot() const;
			const std::vector<ConfigLocation>&	getLocations() const;
			const ConfigLocation&				getLocation(std::string path) const;
			const std::string&					getHttpVersion() const;
			const std::string&					getSignature() const;
			std::size_t							getMaxHeaderSize() const;
			std::size_t							getMaxBodySize() const;
		private:
			int							_port;
			std::string					_host;
			std::vector<std::string>	_serverNames;
			std::string					_root;
			std::vector<ConfigLocation> _locations;
			std::string					_httpVersion;
			std::string					_signature;
			std::size_t			_maxHeaderSize;
			std::size_t			_maxBodySize;
	};
}

#endif