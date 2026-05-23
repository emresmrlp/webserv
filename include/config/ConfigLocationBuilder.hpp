/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigLocationBuilder.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:18:05 by ysumeral          #+#    #+#             */
/*   Updated: 2026/05/19 17:01:19 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGLOCATIONBUILDER_HPP
# define CONFIGLOCATIONBUILDER_HPP
# include <string>
# include <vector>
# include <stdexcept>
# include <algorithm>
# include <iostream>

namespace config
{
	class	ConfigLocation;

	class	ConfigLocationBuilder
	{
		friend class ConfigLocation;

		private:
			std::string					_executePath;
			std::string					_rootPath;
			std::string					_returnRedirection; // NONE (?) ### ERRORPAGES NONE TOO
			//std::string					_uploadPath; // ???
			//std::vector<std::string>		_cgiExt; // ???
			bool						_autoIndex;
			std::vector<std::string>	_allowedMethods;
		public:
			ConfigLocationBuilder();

			ConfigLocationBuilder& setExecutePath(const std::string& executePath);
			ConfigLocationBuilder& setRootPath(const std::string& rootPath);
			ConfigLocationBuilder& setReturnRedirection(const std::string& returnRedirection);
			ConfigLocationBuilder& setAutoIndex(const std::string& str);
			ConfigLocationBuilder& addAllowedMethod(const std::string& method);

			ConfigLocation	build(void);
	};
}

#endif
