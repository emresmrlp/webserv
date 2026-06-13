/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:53:06 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/13 18:24:33 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETEHANDLER_HPP
# define DELETEHANDLER_HPP
# include "IMethodHandler.hpp"

namespace http
{
	class IResponse;
	class ResponseFactory;

	class DeleteHandler : public http::IMethodHandler
	{
		public:
			DeleteHandler();
			~DeleteHandler();
			virtual http::IResponse *handle(const config::ConfigServer *config, 
                const config::ConfigLocation *configLoc, http::Request *request) const;
		private:
            ResponseFactory &_factory;
	};
}

#endif