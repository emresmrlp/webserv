/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:06:11 by ysumeral          #+#    #+#             */
/*   Updated: 2026/05/19 16:55:47 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGSERVER_HPP
# define CONFIGSERVER_HPP
# include <string>
# include <vector>
# include <exception>
# include <cstdlib>
# include <cctype>
# include <map>
# include "ConfigLocation.hpp"

namespace config
{
	struct	ListenTarget
	{
		std::string	host;
		int			port;
		bool		isDefault;
	};

	class ConfigServer
	{
		private:
			std::string					_root;
			std::string					_httpVersion; // NONE
			std::string					_signature; // NONE
			long						_maxHeaderSize;
			long						_maxBodySize;
			std::vector<std::string>	_serverNames;
			std::vector<ConfigLocation> _locations;
			std::vector<ListenTarget>	_listens;
			std::map<int, std::string>	_errorPages;

		public:
			ConfigServer();
			~ConfigServer();

			long	parseByte(std::string str)	const;

			// SETTER FUNCTIONS
			void	setRoot(const std::string& root);
			// bool	setHttpVersion(const std::string& version);
			// bool	setSignature(const std::string& signature);
			bool	setMaxHeaderSize(const std::string& str);
			bool	setMaxBodySize(const std::string& str);
			
			void	addServerName(const std::string& serverName);
			void	addLocation(const ConfigLocation& location);
			bool	addListen(std::string str);
			bool	addErrorPage(std::string no, std::string loc);


			// GETTER FUNCTIONS
			int									getPort()					const;
			const std::string&					getHost()					const;
			const std::string&					getRoot()					const;
			const std::string&					getHttpVersion()			const;
			const std::string&					getSignature()				const;
			const long&							getMaxHeaderSize()			const;
			const long&							getMaxBodySize()			const;
			const std::string&					getErrorPage(int number) 	const;
	
			const std::vector<std::string>&		getServerNames()			const;
			const std::vector<ConfigLocation>&	getLocations()				const;
			const std::vector<ListenTarget>&	getListens()				const;
			const std::map<int, std::string>&	getErrorPages()				const;

			void print() const;
	};
}

#endif