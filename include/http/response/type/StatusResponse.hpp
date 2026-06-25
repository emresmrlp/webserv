/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StatusResponse.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:30 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/13 10:51:23 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORRESPONSE_HPP
# define ERRORRESPONSE_HPP
# include "AResponseBase.hpp"

namespace http
{
    class StatusResponse : public http::AResponseBase
    {
        public:
            StatusResponse(const config::ConfigServer &config, const Request *request, http::StatusCode status);
            ~StatusResponse();
        private:
            void createDefaultBody();
    };
}
#endif