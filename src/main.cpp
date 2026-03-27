/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 15:49:14 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/27 13:11:11 by ysumeral         ###   ########.fr       */
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
#include "Connection.hpp"

#define PORT 8080

int main(int argc, char **argv)
{
    signal(SIGPIPE, SIG_IGN);
    if (argc != 2)
    {
        std::cout << "Correct usage: ./webserv [configuration file]" << std::endl;
        return (1);
    }
    (void)argv;
    
    core::Server server;

    try
    {
        server.init();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
   

    int server_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    while (true) 
    {
        std::cout << "localhost:8080/index.html available." << std::endl;
        int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }
        char buffer[30000] = {0};
        long valread = read(new_socket, buffer, 30000);
        if (valread > 0) 
        {
            core::Connection conn(new_socket, server); 
            
            std::string rawData(buffer);
            conn.appendRequestBuffer(rawData);
            conn.process();
            std::string response = conn.getResponseBuffer();
            send(new_socket, response.c_str(), response.length(), 0);
        }
        close(new_socket);
    }

    close(server_fd);
    return (0);
}

// int main(int argc, char **argv)
// {
//     if (argc != 2)
//     {
//         std::cout << "Correct usage: ./webserv [configuration file]" << std::endl;
//         return (1);
//     }
//     (void)argv;

//     core::Connection conn(42);
//     std::string rawData = 
//         "GET /index.html HTTP/1.1\r\n"
//         "Host: localhost:8080\r\n"
//         "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36\r\n"
//         "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
//         "Accept-Language: tr-TR,tr;q=0.9,en-US;q=0.8,en;q=0.7\r\n"
//         "Accept-Encoding: gzip, deflate, br\r\n";
//     std::string otherRawData =
//         "Connection: keep-alive\r\n"
//         "Upgrade-Insecure-Requests: 1\r\n"
//         "\r\n";
//     std::cout << "-----  REQUEST  -----" << std::endl;
//     std::cout << rawData;
//     std::cout << otherRawData << std::endl;
//     std::cout << "-----  REQUEST END  -----" << std::endl;
//     conn.appendRequestBuffer(rawData);
//     conn.appendRequestBuffer(otherRawData);
//     conn.process();
//     std::cout << "-----  RESPONSE  -----" << std::endl;
//     try
//     {
//         // Returns your response string
//         std::cout << conn.getResponseBuffer() << std::endl;
//     }
//     catch(const std::exception& e)
//     {
//         std::cerr << e.what() << std::endl;
//     }
//     std::cout << "-----  RESPONSE END  -----" << std::endl;
//     return (0);
// }