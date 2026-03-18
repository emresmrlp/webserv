/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 15:49:14 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/18 22:12:54 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
        "POST ../api/upload HTTP/1.1\r\n"
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
        std::cout << "Method: " << conn.getRequest().getMethod() << std::endl;
        std::cout << "Path: " << conn.getRequest().getPath() << std::endl;
        std::cout << "Host: " << conn.getRequest().getHeader("hOst") << std::endl;
        std::cout << "Custom: " << conn.getRequest().getHeader("x-custom-header") << std::endl;
    } 
    else if (conn.getState() == READING)
        std::cout << "ERROR - STATE STILL READING." << std::endl;
    std::cout << "-----  BODY  -----" << std::endl;
    std::cout << conn.getResponse()->serialize() << std::endl;
    std::cout << "-----  BODY END  -----" << std::endl;
    return (0);
}