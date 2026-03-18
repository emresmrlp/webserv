/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 07:37:49 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/18 21:09:04 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP
# include <string>
# include <map>
# include "StatusCode.hpp"

class Request
{
	public:
		Request();
		~Request();
		Request(const Request &ref);
		Request &operator=(const Request &ref);

		StatusCode			parse(std::string &rawReadBuffer);
		const std::string	&getMethod() const;
		const std::string	&getPath() const;
		const std::string	&getVersion() const;
		const std::string	getHeader(const std::string &key) const;
	private:
		// first line
		std::string _method;
		std::string _path;
		std::string _version;
		// other lines
		std::map<std::string, std::string> _headers;
};

#endif