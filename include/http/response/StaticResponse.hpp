/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticResponse.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:30 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/27 18:51:39 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATICRESPONSE_HPP
# define STATICRESPONSE_HPP
# include "AResponseBase.hpp"

namespace http
{
	class Request;
	
	class StaticResponse : public AResponseBase
	{
		public:
			StaticResponse(const config::ConfigServer &config, const http::Request *request, std::size_t bodySize);
			~StaticResponse();
			std::string serialize() const;
		private:
			std::size_t		_bodySize;

			const std::string	getMimeType() const;
			void				createBody();
	};
}

#endif