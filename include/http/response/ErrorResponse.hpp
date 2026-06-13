/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorResponse.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:30 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/13 09:32:57 by ysumeral         ###   ########.fr       */
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
            ErrorResponse(const config::ConfigServer &config, const Request *request, http::StatusCode status);
            ~ErrorResponse();
            std::string serialize() const;
        private:
            void initHeaders();
            void createDefaultBody();
    };
}
#endif