/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 07:37:49 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/18 09:09:47 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUEST_H
# define HTTPREQUEST_H
# include "Config.hpp"
# include <string>
# include <map>

enum    StatusCode
{
    // v0.1.0 only head parse status
    SUCCESS,
    INCOMPLETE,
    BAD_REQUEST
};

class HTTPRequest
{
    public:
        HTTPRequest();
        ~HTTPRequest();
        HTTPRequest(const HTTPRequest &ref);
        HTTPRequest &operator=(const HTTPRequest &ref);

        StatusCode  parse(std::string &rawReadBuffer);
        const std::string &getMethod() const;
        const std::string &getPath() const;
        const std::string &getVersion() const;
        const std::string getHeader(const std::string &key) const;
    private:
        // first line
        std::string _method;
        std::string _path;
        std::string _version;
        // other lines
        std::map<std::string, std::string> _headers;
};

#endif