/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:53:06 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/29 01:42:53 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIHANDLER_HPP
# define CGIHANDLER_HPP
# include <string>
# include <vector>
# include "IMethodHandler.hpp"

namespace config
{
	class ConfigServer;
}

namespace http
{
	struct CGIResult
	{
		bool		status;
		std::string output;
	};

	struct ParsedURI
	{
		std::string scriptPath;
		std::string pathInfo;
		std::string queryString;
	};

	class Request;
	class IResponse;
	class ResponseFactory;

	class CGIHandler : public http::IMethodHandler
	{
		public:
			CGIHandler(ResponseFactory &factory);
			~CGIHandler();
			virtual http::IResponse	*handle(const config::ConfigServer *config, 
                const config::ConfigLocation *iconfigLoc, http::Request *request) const;
			static ParsedURI				parseURI(const std::string &path);
		private:
            ResponseFactory				&_factory;

			CGIResult					executeCgi(std::string resolvePath, std::string interpreterPath,
				std::string tmpInput, char *const *envp) const;
			CGIResult					prepareInput(http::Request *request) const;
			std::vector<std::string>	buildEnv(const config::ConfigServer *config, http::Request *request, ParsedURI URI) const;
	};
}

#endif