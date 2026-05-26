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
# include <map>
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
			std::string							_executePath;
			std::string							_rootPath;
			std::string							_uploadPath;
			std::pair<int, std::string>			_returnRedirection;
			bool								_autoIndex;
			std::map<std::string, std::string>	_cgiPass;
			std::vector<std::string>			_allowedMethods;

			bool								_hasRedirection;
		public:
			ConfigLocationBuilder();

			ConfigLocationBuilder&	setExecutePath(const std::string& executePath);
			ConfigLocationBuilder&	setRootPath(const std::string& rootPath);
			ConfigLocationBuilder&	setUploadPath(const std::string& rootPath);
			ConfigLocationBuilder&	setReturnRedirection(int code, const std::string& url);
			ConfigLocationBuilder&	setAutoIndex(const std::string& str);
			ConfigLocationBuilder&	addCgiPass(const std::string& ext, const std::string& path);
			ConfigLocationBuilder&	addAllowedMethod(const std::string& method);

			ConfigLocation	build(void);
	};
}

#endif
