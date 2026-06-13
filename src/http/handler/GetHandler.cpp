/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 17:00:06 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/13 20:18:46 by ysumeral         ###   ########.fr       */
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
		std::string resolvedPath;
		struct stat st;

		resolvedPath = config->getRoot() + request->getPath();
		if (stat(resolvedPath.c_str(), &st) != 0)
			return (this->_factory.createStatusResponse(config, request, http::NOT_FOUND));
		if (S_ISREG(st.st_mode))
			return (this->_factory.createSuccessResponse(config, request, http::OK));
		if (S_ISDIR(st.st_mode))
		{			
			std::string indexPath;
			
			typedef std::vector<std::string>::const_iterator IndexIt;
			for(IndexIt it = configLoc->getIndexList().begin(); it != configLoc->getIndexList().end(); it++)
			{
				indexPath = (config->getRoot() + "/" + *it);
				if (util::isFileExist(indexPath))
					return (this->_factory.createSuccessResponseWithPath(config, request, indexPath));
			}
			if (configLoc->getAutoIndex())
				return (this->_factory.createAutoIndexResponse(config, request));
		}	
		return (this->_factory.createStatusResponse(config, request, http::FORBIDDEN));
    }
}