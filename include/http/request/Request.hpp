/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 07:37:49 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/29 01:27:33 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP
# include <string>
# include <vector>
# include <utility>

namespace http
{
	class Request
	{
		public:
			Request();
			~Request();
			Request(const Request &ref);
			Request &operator=(const Request &ref);
			
			void				addHeader(const std::string &key, const std::string &value);

			void				setMethod(const std::string &method);
			void				setPath(const std::string &path);
			void				setVersion(const std::string &version);
			void				setBody(const std::string &body);

			const std::string									&getMethod() const;
			const std::string									&getPath() const;
			const std::string									&getVersion() const;
			bool												getHeader(const std::string &key, std::string &value) const;
			bool												getHeaders(const std::string &key, std::vector<std::string> &values) const;
			const std::vector<std::pair<std::string, std::string> >	&getAllHeaders() const;
			const std::string									&getBody() const;
		private:
			std::string											_method;
			std::string											_path;
			std::string											_version;
			std::vector<std::pair<std::string, std::string> >	_headers;
			std::string											_body;
	};
}

#endif