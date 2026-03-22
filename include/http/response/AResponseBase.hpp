/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AResponseBase.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:00:13 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/22 17:26:55 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARESPONSEBASE_HPP
# define ARESPONSEBASE_HPP
# include <string>
# include <sstream>
# include <vector>
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
			AResponseBase();													// init default attributes
			http::StatusCode									_statusCode;
			http::StatusMessage									_statusMessage;
			std::vector<std::pair<std::string, std::string> >	_headers; 		// multi-header support -> vector<pair<>> (Cookie session?)
			std::string											_body;

			std::string			buildHeader() const;
			void				addHeader(const std::string &key, const std::string &value);
			
			void				setBody(const std::string &body);

			bool				getHeader(const std::string &key, std::string &value) const;
			bool				getHeaders(const std::string &key, std::vector<std::string> &values) const;
			std::string			getDate() const;
			http::StatusCode	getStatusCode() const;
			http::StatusMessage	getStatusMessage(http::StatusCode statusCode) const;
	};
}

#endif