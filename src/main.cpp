/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 15:49:14 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/29 01:31:24 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <exception> 
#include <iostream>
#include <string>
#include <vector>
#include "ConfigServer.hpp"
#include "Parser.hpp"
#include "ServerHandler.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Correct usage: ./webserv [configuration file]" << std::endl;
        return (1);
    }
    
    signal(SIGPIPE, SIG_IGN);

    config::Parser parser(argv[1]);
    try
    {
        parser.parse();
        const std::vector<config::ConfigServer>& servers = parser.getServers();
        std::cout << "Parser Debug: Successfully loaded " << servers.size() << " config!" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Parse error: " << e.what() << std::endl;
        return 1;
    }

    if (parser.getServers().empty())
    {
        std::cerr << "Fatal Error: No valid server blocks found in config file." << std::endl;
        return 1;
    }

    try
    {
        core::ServerHandler serverHandler;
        serverHandler.init(parser.getServers());
        serverHandler.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Server Error: " << e.what() << std::endl;
        return (1);
    }
    
    return (0);
}
