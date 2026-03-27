/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:35:30 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/27 16:28:03 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerHandler.hpp"
#include "ConfigLocation.hpp"
#include "ConfigServer.hpp"
#include <vector>

namespace core
{
	ServerHandler::ServerHandler()
	{
		std::vector<config::ConfigServer> serverArray;

		std::vector<config::ConfigLocation> locationsTest;
		config::ConfigLocation loc_one;
		loc_one.setRootPath("www");
		loc_one.setAutoIndex(true);
		std::vector<std::string> _methods;
		_methods.push_back("GET");
		loc_one.setAllowedMethods(_methods);
		loc_one.setExecutePath("/index.html");
		config::ConfigLocation loc_two;
		loc_two.setRootPath("www2");
		loc_two.setAutoIndex(true);
		std::vector<std::string> _methods_two;
		_methods_two.push_back("GET");
		loc_two.setAllowedMethods(_methods_two);
		loc_two.setExecutePath("/index1.html");
		locationsTest.push_back(loc_one);
		locationsTest.push_back(loc_two);
		
		config::ConfigServer server_one;
		server_one.setLocations(locationsTest);
		server_one.setRoot("localhost");
		server_one.setPort(8080);
		std::vector<std::string> namesVector;
		namesVector.push_back("sumeralp.com");
		server_one.setServerNames(namesVector);

		config::ConfigServer server_two;
		server_two.setLocations(locationsTest);
		server_two.setRoot("localhost");
		server_two.setPort(8080);
		std::vector<std::string> namesVector;
		namesVector.push_back("sum.com");
		server_two.setServerNames(namesVector);

		serverArray.push_back(server_one);
		serverArray.push_back(server_two);
	}
	ServerHandler::~ServerHandler() {}
}
