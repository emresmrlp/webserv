/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OkResponse.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:30 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/13 10:45:58 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OKRESPONSE_HPP
# define OKRESPONSE_HPP
# include "AResponseBase.hpp"

namespace http
{
	class Request;
	
	class OkResponse : public AResponseBase
	{
		public:
			OkResponse(const config::ConfigServer &config, const http::Request *request);
			OkResponse(const config::ConfigServer &config, const http::Request *request, const std::string &html);
			~OkResponse();
		private:
			void initHeaders();
		};
}

#endif