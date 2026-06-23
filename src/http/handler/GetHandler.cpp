/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 17:00:06 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/23 05:30:54 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GetHandler.hpp"
#include "IMethodHandler.hpp"
#include "ResponseFactory.hpp"
#include "Util.hpp"
#include <sys/stat.h>

namespace http
{
    GetHandler::GetHandler(ResponseFactory &factory) : _factory(factory) {}

    GetHandler::~GetHandler() {}

    http::IResponse *GetHandler::handle(const config::ConfigServer *config, const config::ConfigLocation *configLoc,
        http::Request *request) const
    {
		struct stat st;

		std::string relativePath = request->getPath().substr(configLoc->getExecutePath().length());
		std::string resolvedPath = util::getRelativeConfigPath(config, configLoc) + relativePath;
		std::cout << "! DEBUG: RESOLVED: " << relativePath << std::endl;
		if (stat(resolvedPath.c_str(), &st) != 0)
			return (this->_factory.createStatusResponse(config, request, http::NOT_FOUND));
		if (S_ISDIR(st.st_mode))
		{
			std::string indexPath;

			if ((relativePath != "/" && relativePath != "") && configLoc->getAutoIndex() == false)
				return (this->_factory.createStatusResponse(config, request, http::NOT_FOUND));
	
			typedef std::vector<std::string>::const_iterator IndexIt;
			for(IndexIt it = configLoc->getIndexList().begin(); it != configLoc->getIndexList().end(); it++)
			{
				indexPath = (util::getRelativeConfigPath(config, configLoc) + "/" + *it);
				if (util::isFileExist(indexPath))
					return (this->_factory.createSuccessResponseWithPath(config, request, indexPath));
			}
			if (configLoc->getAutoIndex())
				return (this->_factory.createAutoIndexResponse(config, request));
		}
		if (S_ISREG(st.st_mode))
			return (this->_factory.createSuccessResponse(config, request, http::OK));
		return (this->_factory.createStatusResponse(config, request, http::FORBIDDEN));
    }
}