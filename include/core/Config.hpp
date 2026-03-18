/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:09:14 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/18 22:05:13 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP
# include <string>
# define MAX_HEADER_SIZE 10000
# define HTTP_VERSION "HTTP/1.1"

class Config
{
    public:
        Config();
    private:
        int         port;
        std::string host;
        std::string root;
};

#endif