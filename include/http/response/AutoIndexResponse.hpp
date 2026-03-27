/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AutoIndexResponse.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:30 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/27 11:01:38 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOINDEXRESPONSE_HPP
# define AUTOINDEXRESPONSE_HPP
# include "AResponseBase.hpp"

namespace http
{
    class AutoIndexResponse : public http::AResponseBase
    {
        public:
            AutoIndexResponse(core::Server server, http::Request request);
            ~AutoIndexResponse();
            std::string serialize() const;
        private:
            void createBody();
    };
}

#endif