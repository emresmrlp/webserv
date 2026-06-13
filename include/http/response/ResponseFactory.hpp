/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseFactory.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 08:41:51 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/13 20:17:57 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSEFACTORY_HPP
# define RESPONSEFACTORY_HPP
# include "StatusCode.hpp"
# include "ConfigServer.hpp"
# include "iostream"

namespace http
{
    class IResponse;
    class Request;
    
    class ResponseFactory
    {
        public:
            ResponseFactory();
            ~ResponseFactory();
            http::IResponse *createAutoIndexResponse(const config::ConfigServer *config, http::Request *request);
            http::IResponse *createSuccessResponse(const config::ConfigServer *config, http::Request *request, http::StatusCode status);
            http::IResponse *createSuccessResponseWithPath(const config::ConfigServer *config, http::Request *request, const std::string &path);
            http::IResponse *createStatusResponse(const config::ConfigServer *config, http::Request *request, http::StatusCode statusCode);
        	http::IResponse *createRedirectResponse(const config::ConfigServer *config, std::pair<int, std::string> redirectPair);
    };
}

#endif