/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseDispatcher.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 12:25:40 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/27 12:41:22 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSEDISPATCHER_HPP
# define RESPONSEDISPATCHER_HPP
# include "Server.hpp"
# include "Request.hpp"
# include "IResponse.hpp"
# include "ResponseFactory.hpp"

namespace http
{
    class ResponseDispatcher
    {
        public:
            ResponseDispatcher(core::Server &server, ResponseFactory &factory);
            ~ResponseDispatcher();
            http::IResponse *dispatch(http::Request &request);
        private:
            core::Server    _server;
            ResponseFactory _factory;
    };
}

#endif