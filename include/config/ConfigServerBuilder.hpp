/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServerBuilder.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 19:39:23 by beldemir          #+#    #+#             */
/*   Updated: 2026/06/07 18:03:58 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGSERVERBUILDER_HPP
# define CONFIGSERVERBUILDER_HPP
# include <string>
# include <vector>
# include <map>
# include <cstdlib>
# include <cctype>
# include <stdexcept>
# include <algorithm>
# include <sstream>
# include <iostream>

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
			std::pair<int, std::string>	_returnRedirection;
			bool						_hasRedirection;

		public:
			ConfigServerBuilder();

			ConfigServerBuilder&	setRoot(const std::string& root);
			ConfigServerBuilder&	setHttpVersion(const std::string& version);
			// ConfigServerBuilder&	setSignature(const std::string& signature);
			ConfigServerBuilder&	setMaxHeaderSize(const std::string& str);
			ConfigServerBuilder&	setMaxBodySize(const std::string& str);
			ConfigServerBuilder&	addServerName(const std::string& serverName);
			ConfigServerBuilder&	addLocation(const ConfigLocation& location);
			ConfigServerBuilder&	addListen(const std::string& str);
			ConfigServerBuilder&	addErrorPage(const std::string& no, const std::string& loc);
			ConfigServerBuilder&	setReturnRedirection(int code, const std::string& url);

			ConfigServer	build(void);
	};
}

#endif