/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 15:49:14 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/18 22:59:00 by ysumeral         ###   ########.fr       */
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
        "GET /index.html?user=gemini HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "User-Agent: Mozilla/5.0 (Macintosh)\r\n"
        "Accept: text/html,application/xhtml+xml\r\n"
        "Accept-Language: tr-TR,tr;q=0.9\r\n"
        "Connection: keep-alive\r\n"
        "X-Custom-Header: Ravenclaw-Logic\r\n"
        "\r\n";
    // add rawData to connection readBuffer
    conn.addReadBuffer(rawData);
    // check connection state, header end (\r\n\r\n) (HTTPRequest.parse() is here)
    conn.update();
    std::cout << "-----  RESPONSE  -----" << std::endl;
    std::cout << conn.getResponse()->serialize() << std::endl;
    std::cout << "-----  RESPONSE END  -----" << std::endl;
    return (0);
}