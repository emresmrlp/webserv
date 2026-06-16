/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedirectResponse.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:44:26 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/16 12:18:46 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RedirectResponse.hpp"
#include <vector>
#include <iostream>
#include <sys/stat.h>

namespace http
{
	RedirectResponse::RedirectResponse(const config::ConfigServer &config, std::pair<int, std::string> redirectPair)
		: AResponseBase(config, NULL)
	{
		this->_statusCode = static_cast<http::StatusCode>(redirectPair.first);
		this->setBody("");
        this->addHeader("Location", ("/" + redirectPair.second));
		this->addHeader("Content-Length", "0");
	}

	RedirectResponse::~RedirectResponse() {}
}