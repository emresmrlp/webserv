/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIResponse.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:30 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/29 01:59:11 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIRESPONSE_HPP
# define CGIRESPONSE_HPP
# include <string>
# include "AResponseBase.hpp"
# include "ConfigServer.hpp"

namespace http
{
	class Request;
	
    enum CGIState
    {
        CGI_STATUSLINE,
        CGI_HEADERS,
        CGI_BODY
    };

	class CGIResponse : public AResponseBase
	{
		public:
			CGIResponse(const config::ConfigServer &config, const http::Request *request, const std::string &path);
			~CGIResponse();
        private:
            CGIState    _state;
            
            bool        parseCGIOutput(const std::string &path);
            bool        parseHeaders(std::string &headersBuffer);
		};
}

#endif