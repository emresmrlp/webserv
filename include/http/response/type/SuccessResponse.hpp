/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SuccessResponse.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:30 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/13 10:45:58 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUCCESSRESPONSE_HPP
# define SUCCESSRESPONSE_HPP
# include "AResponseBase.hpp"

namespace http
{
	class Request;
	
	class SuccessResponse : public AResponseBase
	{
		public:
			SuccessResponse(const config::ConfigServer &config, const http::Request *request, http::StatusCode statusCode);
			SuccessResponse(const config::ConfigServer &config, const http::Request *request, const std::string &path);
			~SuccessResponse();
		private:
			void initHeaders();
		};
}

#endif