/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIResponse.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:30 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/25 12:47:26 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIRESPONSE_HPP
# define CGIRESPONSE_HPP
# include "AResponseBase.hpp"

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
            bool        parseHeaders(std::string &headBuffer);
		};
}

#endif