/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseFactory.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 08:41:51 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/22 17:23:09 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSEFACTORY_HPP
# define RESPONSEFACTORY_HPP
# include "StatusCode.hpp"
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
            http::IResponse *createStaticResponse(const http::Request &request, std::size_t bodySize);
            http::IResponse *createErrorResponse(http::StatusCode statusCode);
            http::IResponse *createAutoIndexResponse(const std::string &directory);
    };
}

#endif