/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 07:37:49 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/19 14:22:53 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP
# include <string>
# include <map>
# include "Config.hpp"
# include "StatusCode.hpp"

enum RequestParseStatus {
    INCOMPLETE,
	FINISHED,
    ERROR
};

class Request
{
	public:
		Request();
		~Request();
		Request(const Request &ref);
		Request &operator=(const Request &ref);

		RequestParseStatus	parse(std::string &rawReadBuffer);
		const std::string	&getMethod() const;
		const std::string	&getPath() const;
		const std::string	&getVersion() const;
		const std::string	&getHeader(const std::string &key) const;
		const std::size_t	&getBodySize() const;
		const std::string	&getBody() const;
		StatusCode			getStatusCode() const;
	private:
		// first line
		std::string _method;
		std::string _path;
		std::string _version;
		StatusCode	_statusCode;
		// other lines
		std::map<std::string, std::string> _headers;
		std::size_t	_bodySize;
		std::string _body;
		const std::string _empty;
};

#endif