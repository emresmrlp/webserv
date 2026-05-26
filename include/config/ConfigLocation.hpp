/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigLocation.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:18:05 by ysumeral          #+#    #+#             */
/*   Updated: 2026/05/19 17:01:19 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGLOCATION_HPP
# define CONFIGLOCATION_HPP
# include <string>
# include <vector>
# include <map>
# include <algorithm>

namespace config
{
	class	ConfigLocationBuilder;

	class	ConfigLocation
	{
		private:
			std::string							_executePath;
			std::string							_rootPath;
			std::string							_uploadPath;
			std::pair<int, std::string>			_returnRedirection;
			std::map<std::string, std::string>	_cgiPass;
			std::vector<std::string>			_allowedMethods;
			bool								_autoIndex;
			bool								_hasRedirection;
		public:
			ConfigLocation(const ConfigLocationBuilder& builder);

			const std::string&				getExecutePath()						const;
			const std::string&				getRootPath()							const;
			const std::string&				getUploadPath()							const;
			std::pair<int, std::string>		getReturnRedirection()					const;
			const std::string&				getCgiPass(const std::string& ext)		const;
			const std::vector<std::string>&	getAllowedMethods()						const;
			bool							isAllowed(const std::string& method)	const;
			bool							getAutoIndex()							const;
			bool							hasRedirection()						const;

			void	print() const;
	};
}

#endif