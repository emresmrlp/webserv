/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseFactory.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 10:07:42 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/05 19:36:28 by ysumeral         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "ResponseFactory.hpp"
#include "ErrorResponse.hpp"
#include "OkResponse.hpp"
#include <dirent.h>

namespace http
{
	ResponseFactory::ResponseFactory() {}

	ResponseFactory::~ResponseFactory() {}

	http::IResponse *ResponseFactory::createErrorResponse(const config::ConfigServer *config, const std::string &path, http::StatusCode statusCode)
	{
		return (new ErrorResponse(*config, path, statusCode));
	}

	http::IResponse *ResponseFactory::createOkResponse(const config::ConfigServer *config, http::Request *request)
	{
		return (new OkResponse(*config, request));
	}

	http::IResponse *ResponseFactory::createAutoIndexResponse(const config::ConfigServer *config, http::Request *request)
	{
		std::string html;

		html = this->generateAutoIndexResponse(config, request);
		return (new OkResponse(*config, request, html));
	}

	const std::string     ResponseFactory::generateAutoIndexResponse(const config::ConfigServer *config, http::Request *request)
	{
		std::stringstream   body_oss;
		std::string         fileName;
		DIR* dir;

		body_oss << "<!DOCTYPE html><html><head><title>Webserv - Index of " << request->getPath() << "</title></head>"    
			<< "<body style='font-size: 24px;'><h1>" << "Webserv - Index of " << request->getPath() << "</h1>"
			<< "<hr>"
			<< "<a href='../' style='display: block;'>../</a>\n";
		dir = opendir((config->getRoot() + "/" + request->getPath()).c_str());
		if (dir != NULL)
		{
			struct dirent *ent;

			while ((ent = readdir(dir)) != NULL)
			{
				fileName = ent->d_name;
				if (fileName != "." && fileName != "..")
					body_oss << "<a href='" << fileName << "' style='display: block;'>" << fileName << "</a>\n";
			}
			closedir(dir);
		}
		
		body_oss << "<hr></body></html>";
		return (body_oss.str());
	}
}