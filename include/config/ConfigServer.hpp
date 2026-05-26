/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:06:11 by ysumeral          #+#    #+#             */
/*   Updated: 2026/05/25 16:15:30 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGSERVER_HPP
# define CONFIGSERVER_HPP
# include "ConfigLocation.hpp"
# include <string>
# include <vector>
# include <map>

namespace config
{
	class	ConfigLocation;

	class	ConfigLocationBuilder;

	class	ConfigServerBuilder;

	struct	ListenTarget
	{
		std::string	host;
		int			port;
		bool		isDefault;
	};

	class	ConfigServer
	{
		private:
			std::string					_root;
			std::string					_httpVersion;
			std::string					_signature;
			long						_maxHeaderSize;
			long						_maxBodySize;
			std::vector<std::string>	_serverNames;
			std::vector<ConfigLocation>	_locations;
			std::vector<ListenTarget>	_listens;
			std::map<int, std::string>	_errorPages;

		public:
			ConfigServer(const ConfigServerBuilder& builder);

			int									getPort()					const;
			const std::string&					getHost()					const;
			const std::string&					getRoot()					const;
			const std::string&					getHttpVersion()			const;
			const std::string&					getSignature()				const;
			std::size_t							getMaxHeaderSize()			const;
			std::size_t							getMaxBodySize()			const;
			const std::string&					getErrorPage(int number) 	const;
	
			const std::vector<std::string>&		getServerNames()			const;
			const std::vector<ConfigLocation>&	getLocations()				const;
			const std::vector<ListenTarget>&	getListens()				const;
			const std::map<int, std::string>&	getErrorPages()				const;
		
			const ConfigLocation*				getLocation(const std::string& str)	const;

			void	print() const;
	};
}

#endif