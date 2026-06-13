/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PostHandler.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:58:56 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/13 20:56:03 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POSTHANDLER_HPP
# define POSTHANDLER_HPP
# include "IMethodHandler.hpp"

namespace http
{
	class IResponse;
    class ResponseFactory;

    class PostHandler : public http::IMethodHandler
    {
        public:
            PostHandler(ResponseFactory &factory);
            ~PostHandler();
            virtual http::IResponse *handle(const config::ConfigServer *config, 
                const config::ConfigLocation *configLoc, http::Request *request) const;
        private:
            ResponseFactory &_factory;
    };
}

#endif