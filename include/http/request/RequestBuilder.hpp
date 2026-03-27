/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestBuilder.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 08:47:02 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/27 11:47:39 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTBUILDER_HPP
# define REQUESTBUILDER_HPP
# include <string>
# include <vector>
# include "Server.hpp"
# include "StatusCode.hpp"

namespace http
{
	enum ParseState
	{
		STATE_REQUEST_LINE,
		STATE_HEADERS,
		STATE_BODY,
		STATE_WAIT_VALIDATE,
		STATE_COMPLETE,
		STATE_ERROR
	};

	enum ParseStatus
	{
		INCOMPLETE,
		COMPLETE,
		ERROR
	};

	struct ParseResult
	{
		http::ParseStatus	parseStatus;
		http::StatusCode	httpStatusCode;
	};

	class Request;

	class RequestBuilder
	{
		public:
			RequestBuilder(core::Server server);
			~RequestBuilder();

			http::ParseResult	parse(std::string &rawReadBuffer);
			void				reset();
			void				appendBody(const std::string &buffer);
			Request				*build();
		private:
			std::string											_method;
			std::string											_path;
			std::string											_version;
			std::vector<std::pair<std::string, std::string> >	_headers;
			std::string											_body;

			core::Server										&_server;
			bool												_hasBody;
			ParseState											_state;
			ParseResult											_parseResult;
			http::ParseResult	handleParseResult(http::StatusCode statusCode, http::ParseStatus parseStatus);
			bool				getHeaders(const std::string &key, std::vector<std::string> &values) const;
			void				addHeader(const std::string &key, const std::string &value);
			bool				buildRequestLine(std::string &line);
			bool				buildHeaderLine(std::string &line);
			bool				buildBody(std::string &rawReadBuffer);
			bool				validateParseResult();
	};
}

#endif