/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 15:49:14 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/19 15:19:26 by ysumeral         ###   ########.fr       */
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
        "GET /redirect.html HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36\r\n"
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
        "Accept-Language: tr-TR,tr;q=0.9,en-US;q=0.8,en;q=0.7\r\n"
        "Accept-Encoding: gzip, deflate, br\r\n";
    std::string otherRawData =
        "Connection: keep-alive\r\n"
        "Upgrade-Insecure-Requests: 1\r\n"
        "\r\n";
    // add rawData to connection readBuffer
    std::cout << "-----  REQUEST  -----" << std::endl;
    std::cout << rawData << std::endl;
    std::cout << otherRawData << std::endl;
    std::cout << "-----  REQUEST END  -----" << std::endl;
    conn.addReadBuffer(rawData);
    conn.addReadBuffer(otherRawData);
    conn.prepareRequest();
    conn.prepareResponse();
    // check connection state, header end (\r\n\r\n) (HTTPRequest.parse() is here)
    std::cout << "-----  RESPONSE  -----" << std::endl;
    try
    {
       std::cout << conn.getResponse()->serialize() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "-----  RESPONSE END  -----" << std::endl;
    return (0);
}