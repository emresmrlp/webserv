/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeadHandler.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:58:45 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/13 19:10:47 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADHANDLER_HPP
# define HEADHANDLER_HPP
# include "IMethodHandler.hpp"
# include "GetHandler.hpp"

namespace http
{
	class IResponse;
    class ResponseFactory;

    class HeadHandler : public http::IMethodHandler
    {
        public:
            HeadHandler(ResponseFactory &factory);
            ~HeadHandler();
            virtual http::IResponse *handle(const config::ConfigServer *config, 
                const config::ConfigLocation *configLoc, http::Request *request) const;
        private:
            GetHandler      _getHandler;
    };
}

#endif