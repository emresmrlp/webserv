/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PutHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:58:35 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/13 18:24:30 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUTHANDLER_HPP
# define PUTHANDLER_HPP
# include "IMethodHandler.hpp"

namespace http
{
	class IResponse;
    class ResponseFactory;

    class PutHandler : public http::IMethodHandler
    {
        public:
            PutHandler();
            ~PutHandler();
            virtual http::IResponse *handle(const config::ConfigServer *config, 
                const config::ConfigLocation *configLoc, http::Request *request) const;
        private:
            ResponseFactory &_factory;
    };
}

#endif