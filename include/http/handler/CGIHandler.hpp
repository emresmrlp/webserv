/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:53:06 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/24 16:29:26 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIHANDLER_HPP
# define CGIHANDLER_HPP
# include "IMethodHandler.hpp"

namespace http
{
	struct CGIResult
	{
		bool		status;
		std::string output;
	};

	class IResponse;
	class ResponseFactory;

	class CGIHandler : public http::IMethodHandler
	{
		public:
			CGIHandler(ResponseFactory &factory);
			~CGIHandler();
			virtual http::IResponse *handle(const config::ConfigServer *config, 
                const config::ConfigLocation *iconfigLoc, http::Request *request) const;
		private:
            ResponseFactory				&_factory;

			const std::string			getQuery(const std::string &path) const;
			CGIResult					executeCgi(std::string resolvePath, std::string interpreterPath,
				std::string tmpInput, char *const *envp) const;
			CGIResult					prepareInput(http::Request *request) const;
			std::vector<std::string>	buildEnv(const config::ConfigServer *config, http::Request *request) const;
	};
}

#endif