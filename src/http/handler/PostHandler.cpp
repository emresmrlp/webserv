/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PostHandler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 17:02:59 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/13 19:49:26 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PostHandler.hpp"

namespace http
{
	PostHandler::PostHandler()
	{
	}

	PostHandler::~PostHandler()
	{
	}

	http::IResponse *PostHandler::handle(const config::ConfigServer *config, const config::ConfigLocation *configLoc,
		http::Request *request) const
	{}
}