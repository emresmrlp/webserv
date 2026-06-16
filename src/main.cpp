/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 15:49:14 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/16 11:41:49 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "AResponseBase.hpp"
#include "ConfigServer.hpp"
#include "Server.hpp"
#include "ServerHandler.hpp"
#include "Connection.hpp"
#include "Parser.hpp"
#include "signal.h"

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
