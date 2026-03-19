/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IResponse.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 12:26:56 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/18 22:06:08 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRESPONSE_HPP
# define IRESPONSE_HPP
# include <string>
# include "Config.hpp"
# include "StatusCode.hpp"

class IResponse
{
    public:
        virtual ~IResponse() {};
        virtual StatusCode getStatusCode() const = 0;
        virtual std::string serialize() const = 0;
};

#endif