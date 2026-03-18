/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AResponseBase.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:00:13 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/18 22:02:39 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARESPONSEBASE_HPP
# define ARESPONSEBASE_HPP
# include <string>
# include <sstream>
# include "IResponse.hpp"

class AResponseBase : public IResponse
{
	protected:
		StatusCode	_statusCode;
		std::string	_statusMessage;
	public:
		virtual ~AResponseBase() {};
		static  std::string getStatusMessage(StatusCode statusCode);
		virtual StatusCode getStatusCode() const;
		virtual std::string serialize() const = 0;
};

#endif