/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AResponseBase.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:00:13 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/29 01:54:28 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARESPONSEBASE_HPP
# define ARESPONSEBASE_HPP
# include <string>
# include <utility>
# include <vector>
# include "ConfigServer.hpp"
# include "IResponse.hpp"
# include "StatusCode.hpp"

namespace http
{	
	class Request;
	class AResponseBase : public http::IResponse
	{
		public:
			virtual				~AResponseBase() {};
			virtual std::string	serialize() const;
			void				clearBody();
		protected:
			AResponseBase(const config::ConfigServer &config, const http::Request *request);
			http::StatusCode									_statusCode;
			std::vector<std::pair<std::string, std::string> >	_headers;
			std::string											_body;
			config::ConfigServer								_config;
			std::string											_signature;
			const http::Request									*_request;

			std::string			buildStatusLine() const;
			std::string			buildHeader() const;
			void				addHeader(const std::string &key, const std::string &value);
			
			void				setBody(const std::string &body);
			void				createBody();
			void				createBody(const std::string &path);
			std::string			readFile(const std::string &filePath);
			void				initDefaultHeaders();

			bool				getHeader(const std::string &key, std::string &value) const;
			bool				getHeaders(const std::string &key, std::vector<std::string> &values) const;
			http::StatusCode	getStatusCode() const;
			http::StatusMessage	getStatusMessage(http::StatusCode statusCode) const;
	};
}

#endif