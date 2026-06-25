/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIResponse.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 10:34:30 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/25 13:30:44 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIResponse.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:26 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/05 17:08:48 by ysumeral         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "CGIResponse.hpp"
#include "StatusCode.hpp"
#include <iostream>
#include "Request.hpp"
#include <iomanip>
#include <sstream>
#include <dirent.h>
#include <map>
#include "Util.hpp"
#include <cstdio>
#include <fstream>

namespace http
{
    CGIResponse::CGIResponse(const config::ConfigServer &config, const Request *request, const std::string &path)
        : AResponseBase(config, request)
    {
        this->_state = CGI_STATUSLINE;
        if (this->parseCGIOutput(path) == false)
        {
            std::remove(path.c_str());
            this->_statusCode = http::INTERNAL_SERVER_ERROR;
            this->_body = "500 Internal Server Error";
        }
        this->addHeader("Content-Length", util::toString(this->_body.size()));
    }

    CGIResponse::~CGIResponse() {}

    bool CGIResponse::parseCGIOutput(const std::string &path)
    {
        std::ifstream file(path.c_str(), std::ios::binary);
        if (!file.is_open())
            return (false);
        
        char buffer[4096];
        std::string headBuffer;
        std::string bodyBuffer;
        std::size_t pos = std::string::npos;

        while (file.read(buffer, sizeof(buffer)) || file.gcount() > 0)
        {
            headBuffer.append(buffer, file.gcount());
            pos = headBuffer.find("\r\n\r\n");
            if (pos != std::string::npos)
                break;
            if (headBuffer.size() > 8192)
            {
                file.close();
                return (false); 
            }
        }
        if (pos == std::string::npos)
        {
            file.close();
            return (false); 
        }

        bodyBuffer = headBuffer.substr(pos + 4);
        while (file.read(buffer, sizeof(buffer)) || file.gcount() > 0)
            bodyBuffer.append(buffer, file.gcount());
        this->setBody(bodyBuffer);
        if (this->parseHeaders(headBuffer) == false)
            return (false);

        std::remove(path.c_str());
        return (true);
    }
    
    bool CGIResponse::parseHeaders(std::string &)
    {
        this->_statusCode = OK; 
        this->addHeader("Content-Type", "text/html");
        return (true);
    }
}