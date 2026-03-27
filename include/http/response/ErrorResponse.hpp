/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorResponse.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:30 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/27 13:13:30 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORRESPONSE_HPP
# define ERRORRESPONSE_HPP
# include "AResponseBase.hpp"

namespace http
{
    class ErrorResponse : public http::AResponseBase
    {
        public:
            ErrorResponse(core::Server server, http::StatusCode status);
            ~ErrorResponse();
            std::string serialize() const;
        private:
            void createBody();
    };
}
#endif