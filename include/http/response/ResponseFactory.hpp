/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseFactory.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 08:41:51 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/05 19:33:14 by ysumeral         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
            http::IResponse *createOkResponse(const config::ConfigServer *config, http::Request *request);
            http::IResponse *createErrorResponse(const config::ConfigServer *config, const std::string &path, http::StatusCode statusCode);
        private:
            const std::string   generateAutoIndexResponse(const config::ConfigServer *config, http::Request *request);
    };
}

#endif