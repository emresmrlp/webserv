/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServerBuilder.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 19:39:23 by beldemir          #+#    #+#             */
/*   Updated: 2026/06/29 11:31:03 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGSERVERBUILDER_HPP
# define CONFIGSERVERBUILDER_HPP
# include "ConfigLocation.hpp"
# include "ConfigServer.hpp"
# include <string>
# include <vector>
# include <map>
# include <cstdlib>
# include <cctype>

namespace config
{
	class	ConfigLocation;

	class	ConfigLocationBuilder;

	struct	ListenTarget;

	class	ConfigServer;

	class	ConfigServerBuilder
	{
		friend class ConfigServer;

		private:
			std::string					_root;
			std::string					_httpVersion;
			std::string					_signature;
			size_t						_maxHeaderSize;
			size_t						_maxBodySize;
			std::vector<std::string>	_serverNames;
			std::vector<ConfigLocation> _locations;
			std::vector<ListenTarget>	_listens;
			std::map<int, std::string>	_errorPages;

		public:
			ConfigServerBuilder();

			ConfigServerBuilder&	setRoot(const std::string& root);
			ConfigServerBuilder&	setHttpVersion(const std::string& version);
			ConfigServerBuilder&	setMaxHeaderSize(const std::string& str);
			ConfigServerBuilder&	setMaxBodySize(const std::string& str);
			ConfigServerBuilder&	addServerName(const std::string& serverName);
			ConfigServerBuilder&	addLocation(const ConfigLocation& location);
			ConfigServerBuilder&	addListen(const std::string& str);
			ConfigServerBuilder&	addErrorPage(const std::string& no, const std::string& loc);

			ConfigServer	build(void);
	};
}

#endif