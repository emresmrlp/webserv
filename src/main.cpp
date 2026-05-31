/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 15:49:14 by ysumeral          #+#    #+#             */
/*   Updated: 2026/05/31 14:39:33 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "AResponseBase.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <signal.h>
#include "ConfigServer.hpp"
#include "Server.hpp"
#include "ServerHandler.hpp"
#include "Connection.hpp"
#include "Parser.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Correct usage: ./webserv [configuration file]" << std::endl;
        return (1);
    }
    
    signal(SIGPIPE, SIG_IGN); // ? want to write on closed pipe -> ignore

    config::Parser parser(argv[1]);
    try
    {
        parser.parse();
        const std::vector<config::ConfigServer>& servers = parser.getServers();
        std::cout << "Successfully loaded " << servers.size() << " servers!" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Parse error: " << e.what() << std::endl;
        return 1;
    }
    if (parser.getServers().empty()) {
        std::cerr << "Fatal Error: No valid server blocks found in config file." << std::endl;
        return 1;
    }

    core::ServerHandler serverHandler;
    serverHandler.init(parser.getServers());
    serverHandler.run();
    return (0);
}
