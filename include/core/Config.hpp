/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:09:14 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/19 16:57:51 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP
# include <string>
# include <vector>
# define MAX_HEADER_SIZE 8192
# define MAX_BODY_SIZE 1048576
# define HTTP_VERSION "HTTP/1.1"
# define CRLF "\r\n"
# define DOUBLE_CRLF "\r\n\r\n"
# define SERVER_NAME "Webserv v0.1.2"
# define ALLOWED_METHODS "GET" // this sytnax must be like "GET, POST, DELETE" and ve need to seperated vector<std::string> allowed_methods;
# define AUTOINDEX 0 // on -> 1, off -> 0;
# define ROOT "www"
# define INDEX "index.html"

#endif