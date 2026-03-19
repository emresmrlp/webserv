/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticResponse.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:30 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/19 08:33:50 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATICRESPONSE_HPP
# define STATICRESPONSE_HPP
# include "AResponseBase.hpp"

class Request;

class StaticResponse : public AResponseBase
{
    public:
        StaticResponse(Request &request, std::size_t bodySize);
        std::string serialize() const;
    private:
        const std::string createBody() const;
        Request     &_request;
        std::size_t	_bodySize;
};

#endif