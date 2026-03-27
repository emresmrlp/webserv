/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigLocation.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:18:05 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/27 08:19:43 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGLOCATION_HPP
# define CONFIGLOCATION_HPP
# include <string>
# include <vector>

namespace config
{
	class ConfigLocation
	{
		public:
			ConfigLocation();
			~ConfigLocation();

			void setRootPath(const std::string& rootPath);
			void setExecutePath(const std::string& executePath);
			void setReturnRedirection(const std::string& returnRedirection);
			void setAllowedMethods(const std::vector<std::string>& allowedMethods);
			void setAutoIndex(bool autoIndex);
			const std::string& getRootPath() const;
			const std::string& getExecutePath() const;
			const std::string& getReturnRedirection() const;
			const std::vector<std::string>& getAllowedMethods() const;
			bool getAutoIndex() const;
		private:
			std::string					_rootPath;
			std::string					_executePath;
			std::string					_returnRedirection;
			std::vector<std::string>	_allowedMethods;
			bool						_autoIndex;
	};
}

#endif