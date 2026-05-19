/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigLocation.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:18:05 by ysumeral          #+#    #+#             */
/*   Updated: 2026/05/19 14:26:06 by beldemir         ###   ########.fr       */
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
		private:
			std::string					_executePath;
			std::string					_rootPath;
			std::string					_returnRedirection; // NONE (?) ### ERRORPAGES NONE TOO
			std::vector<std::string>	_allowedMethods; // NO-LIMIT YET, IT SHOULD LIMIT ONLY FOR GET SET POST etc.
			bool						_autoIndex;
		public:
			ConfigLocation();
			~ConfigLocation();

			// SETTER FUNCTIONS
			bool setExecutePath(const std::string& executePath);
			bool setRootPath(const std::string& rootPath);
			bool setReturnRedirection(const std::string& returnRedirection);
			bool setAutoIndex(std::string str);

			bool addAllowedMethod(const std::string& method);

			
			// GETTER FUNCTIONS
			const std::string&				getExecutePath()		const;
			const std::string&				getRootPath()			const;
			const std::string&				getReturnRedirection()	const;
			bool							getAutoIndex()			const;

			const std::vector<std::string>&	getAllowedMethods()		const;


			void print() const;
		};
}

#endif