/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AResponseBase.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:00:13 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/10 13:42:05 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARESPONSEBASE_HPP
# define ARESPONSEBASE_HPP
# include <string>
# include <sstream>
# include <vector>
# include "Server.hpp"
# include "Request.hpp"
# include "StatusCode.hpp"
# include "IResponse.hpp"

namespace http
{	
	class AResponseBase : public http::IResponse
	{
		public:
			virtual ~AResponseBase() {};
			virtual std::string serialize() const = 0;
		protected:
			AResponseBase(const config::ConfigServer &config, const http::Request *request);
			http::StatusCode									_statusCode;
			http::StatusMessage									_statusMessage;
			std::vector<std::pair<std::string, std::string> >	_headers; 		// multi-header support -> vector<pair<>> (Cookie session?)
			std::string											_body;
			config::ConfigServer								_config;
			std::string											_signature;
			const http::Request									*_request;

			std::string			buildHeader() const;
			void				addHeader(const std::string &key, const std::string &value);
			
			void				setBody(const std::string &body);
			void				createBody();
			void				createBody(const std::string &literalPath);
			std::string			readFile(const std::string &filePath);

			bool				getHeader(const std::string &key, std::string &value) const;
			bool				getHeaders(const std::string &key, std::vector<std::string> &values) const;
			std::string			getDate() const;
			const std::string	getMimeType(const std::string &path) const;
			http::StatusCode	getStatusCode() const;
			http::StatusMessage	getStatusMessage(http::StatusCode statusCode) const;
	};
}

#endif