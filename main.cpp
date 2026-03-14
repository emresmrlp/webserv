/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 15:49:14 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/14 15:51:52 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Correct usage: ./webserv [configuration file]" << std::endl;
        return (1);
    }
    std::cout << "File \"" << argv[1] << "\" will be execute soon..." << std::endl;
    return (0);
}