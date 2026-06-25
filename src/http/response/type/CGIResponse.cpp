/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIResponse.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 10:34:30 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/25 18:57:01 by ysumeral         ###   ########.fr       */
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
        std::string headersBuffer;
        std::string bodyBuffer;
        std::size_t pos = std::string::npos;

        while (file.read(buffer, sizeof(buffer)) || file.gcount() > 0)
        {
            headersBuffer.append(buffer, file.gcount());
            pos = headersBuffer.find("\r\n\r\n");
            if (pos != std::string::npos)
                break;
            if (headersBuffer.size() > 8192)
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

        bodyBuffer = headersBuffer.substr(pos + 4);
        headersBuffer.erase(pos + 4);
        while (file.read(buffer, sizeof(buffer)) || file.gcount() > 0)
            bodyBuffer.append(buffer, file.gcount());
        this->setBody(bodyBuffer);
        if (this->parseHeaders(headersBuffer) == false)
            return (false);
        std::remove(path.c_str());
        return (true);
    }
    
    bool CGIResponse::parseHeaders(std::string &headersBuffer)
    {
        std::size_t pos;
        std::string line;
        std::vector<std::string> headers;
        
        this->_statusCode = http::OK; 
        while (!headersBuffer.empty())
        {
            pos = headersBuffer.find_first_of(CRLF);
            if (pos == std::string::npos)
                break ;
            if (pos == 0)
            {
                headersBuffer.erase(0, 2);
                break ;
            }
            line = headersBuffer.substr(0, pos);
            if (!(line.empty()) && (line[0] == ' ' || line[0] == '\t'))
				return (false);
            std::size_t sep = line.find(":");
            if (sep == std::string::npos
                || sep == 0)
                return (false);
            std::string key = line.substr(0, sep);
            std::string value = line.substr(sep + 1);
            if (key.find_first_of(" \t") != std::string::npos
                || key.find(" ") != std::string::npos) 
                return (false);
            std::size_t firstSpace = value.find_first_not_of(" \t");
            if (firstSpace == std::string::npos) 
                value = "";
            else
            {
                std::size_t lastSpace = value.find_last_not_of(" \t");
                value = value.substr(firstSpace, lastSpace + 1);
            }
            if (key != "Status")
                this->addHeader(key, value);
            else
            {
                std::cout << "! DEBUG: value: " << value << std::endl;
                value.substr(0, value.find_first_of(" "));
                this->_statusCode = static_cast<http::StatusCode>(std::atoi(value.c_str()));
            }
            headersBuffer.erase(0, pos + 2);
        }
        return (true);
    }
}