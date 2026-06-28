/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedirectResponse.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:30 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/29 02:00:37 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTRESPONSE_HPP
# define REDIRECTRESPONSE_HPP
# include <string>
# include <utility>
# include "AResponseBase.hpp"
# include "ConfigServer.hpp"

namespace http
{
    class RedirectResponse : public http::AResponseBase
    {
        public:
            RedirectResponse(const config::ConfigServer &config, std::pair<int, std::string> redirectPair);
            ~RedirectResponse();
    };
}

#endif