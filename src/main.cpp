/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 15:49:14 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/18 16:39:11 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Connection.hpp"
#include "AResponseBase.hpp"

#include <iostream>
#include "Connection.hpp"
#include "AResponseBase.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Correct usage: ./webserv [configuration file]" << std::endl;
        return (1);
    }
    (void)argv;

    Connection conn(42);

    //example HTTP POST request
    std::string rawData = 
        "POST  /api/upload   ssfsfs   HTTP/1.1\r\n"
        "Host: localhost:8002\r\n"
        "Content-Type: application/json\r\n"
        "X-Custom-Header:   Slytherin-Logic\r\n"
        "\r\n";
    // add rawData to connection readBuffer
    conn.addReadBuffer(rawData);
    // check connection state, header end (\r\n\r\n) (HTTPRequest.parse() is here)
    conn.update();
    if (conn.getState() == WRITING)
    {
        std::cout << "SUCCESS ->-> STATE READING -> WRITING" << std::endl;
        std::cout << "--- PARSED HTTP VALUES LIST (HTTPREQUEST) ---" << std::endl;
        //getRequest() goes to Connection->HTTPRequest object. we need to delete this after
        std::cout << "Method: " << conn.getRequest().getMethod() << std::endl;
        std::cout << "Path: " << conn.getRequest().getPath() << std::endl;
        std::cout << "Host: " << conn.getRequest().getHeader("hOst") << std::endl;
        std::cout << "Custom: " << conn.getRequest().getHeader("x-custom-header") << std::endl;
    } 
    else if (conn.getState() == READING)
        std::cout << "ERROR - STATE STILL READING." << std::endl;

    std::cout << "--- BAD INPUT TEST ---" << std::endl;
    Connection badConn(43);
    badConn.addReadBuffer("GEEEET / HTTP/1.1\r\n\r\n");
    badConn.update();
    if (badConn.getState() != READING)
        std::cout << "SUCCESS ->-> NO BAD REQUEST FOUND." << std::endl;
    return (0);
}