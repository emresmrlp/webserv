/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticResponse.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:30 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/18 22:23:04 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATICRESPONSE_HPP
# define STATICRESPONSE_HPP
# include "AResponseBase.hpp"

class Request;

class StaticResponse : public AResponseBase
{
    public:
        StaticResponse(Request &request);
        std::string serialize() const;
    private:
        Request &_request;
};

#endif