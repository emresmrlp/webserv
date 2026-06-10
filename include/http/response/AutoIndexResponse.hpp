/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AutoIndexResponse.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:30 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/10 13:46:53 by ysumeral         ###   ########.fr       */
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
			std::string serialize() const;
		private:
            void createDefaultBody();
			void initHeaders();
		};
}

#endif