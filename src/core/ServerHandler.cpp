/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:35:30 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/28 11:24:39 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerHandler.hpp"
#include "ConfigLocation.hpp"
#include "ConfigServer.hpp"
#include <vector>

namespace core
{
	ServerHandler::ServerHandler() {}

	void ServerHandler::createServer(config::ConfigServer &config_one, config::ConfigServer &config_two)
	{
		std::cout << "+ ServerHandler -> createServer method called." << std::endl;
		std::vector<config::ConfigLocation> locationsTest;
		config::ConfigLocation default_loc;
		std::vector<std::string> methods;

		default_loc.setRootPath("www");
		default_loc.setAutoIndex(true);
		methods.push_back("GET");
		default_loc.setAllowedMethods(methods);
		default_loc.setExecutePath("/");
		locationsTest.push_back(default_loc);

		config_one.setLocations(locationsTest);
		config_one.setRoot("www");
		config_one.setPort(8080);
		std::vector<std::string> names_one;
		names_one.push_back("sumeralp.com");
		config_one.setServerNames(names_one);

		config_two.setLocations(locationsTest);
		config_two.setRoot("www2");
		config_two.setPort(8080);
		std::vector<std::string> names_two;
		names_two.push_back("sum.com");
		config_two.setServerNames(names_two);

		this->_servers.clear();
		this->_servers.push_back(core::Server(config_one));
		this->_servers.push_back(core::Server(config_two));
		std::cout << "+ ServerHandler -> Servers created success." << std::endl;
	}

	const std::vector<core::Server>& ServerHandler::getServers() const
	{
		return (this->_servers);
	}

	ServerHandler::~ServerHandler() {}
}
