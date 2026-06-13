/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AutoIndexResponse.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:30 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/13 10:45:50 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOINDEXRESPONSE_HPP
# define AUTOINDEXRESPONSE_HPP
# include "AResponseBase.hpp"

namespace http
{
	class Request;
	
	class AutoIndexResponse : public AResponseBase
	{
		public:
			AutoIndexResponse(const config::ConfigServer &config, const http::Request *request);
			~AutoIndexResponse();
		private:
            void createDefaultBody();
			void initHeaders();
		};
}

#endif