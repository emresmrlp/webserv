/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedirectResponse.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:30 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/06 10:15:59 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTRESPONSE_HPP
# define REDIRECTRESPONSE_HPP
# include "AResponseBase.hpp"

namespace http
{
    class RedirectResponse : public http::AResponseBase
    {
        public:
            RedirectResponse(const config::ConfigServer &config, std::pair<int, std::string> redirectPair);
            ~RedirectResponse();
            std::string serialize() const;
    };
}
#endif