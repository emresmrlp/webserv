/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AutoIndexResponse.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:30 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/19 13:13:37 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOINDEXRESPONSE_HPP
# define AUTOINDEXRESPONSE_HPP
# include "AResponseBase.hpp"

class Request;

class AutoIndexResponse : public AResponseBase
{
    public:
        AutoIndexResponse();
        std::string serialize() const;
};

#endif