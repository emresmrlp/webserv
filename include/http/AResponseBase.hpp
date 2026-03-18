/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AResponseBase.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:00:13 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/18 13:41:45 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARESPONSEBASE_HPP
# define ARESPONSEBASE_HPP
# include <string>
# include "IResponse.hpp"

class AResponseBase : public IResponse
{
    protected:
        StatusCode _statusCode;
    public:
        virtual ~AResponseBase() {};
        virtual StatusCode getStatusCode() const;
        virtual std::string &serialize() const = 0;
};

#endif