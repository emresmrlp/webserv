/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigLocationBuilder.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:18:05 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/29 11:22:24 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGLOCATIONBUILDER_HPP
# define CONFIGLOCATIONBUILDER_HPP
# include "Util.hpp"
# include <string>
# include <vector>
# include <map>
# include <cstddef>
# include <utility>

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
			std::vector<std::string>			_indexList;
			bool								_hasRedirection;
			size_t								_maxHeaderSize;
			size_t								_maxBodySize;
		public:
			ConfigLocationBuilder();

			ConfigLocationBuilder&	setExecutePath(const std::string& executePath);
			ConfigLocationBuilder&	setRootPath(const std::string& rootPath);
			ConfigLocationBuilder&	setUploadPath(const std::string& rootPath);
			ConfigLocationBuilder&	setReturnRedirection(int code, const std::string& url);
			ConfigLocationBuilder&	setAutoIndex(const std::string& str);
			ConfigLocationBuilder&	addCgiPass(const std::string& ext, const std::string& path);
			ConfigLocationBuilder&	addAllowedMethod(const std::string& method);
			ConfigLocationBuilder&	addToIndexList(const std::string& index);

			ConfigLocationBuilder&	setMaxHeaderSize(const std::string& str);
			ConfigLocationBuilder&	setMaxBodySize(const std::string& str);

			ConfigLocation	build(void);
	};
}

#endif
