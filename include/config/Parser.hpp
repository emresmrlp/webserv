/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 19:39:23 by beldemir          #+#    #+#             */
/*   Updated: 2026/05/03 17:22:34 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include "Token.hpp"
# include "ConfigServer.hpp"
# include <vector>
# include <string>

namespace   config
{
    class   Parser
    {
        private:
            const std::vector<config::Token>&   _tokens;
            size_t                              _pos;

            config::Token   curr(void);
            ConfigServer    parseServer(void);
            ConfigLocation  parseLocation(void);

        public:
            Parser(const std::vector<config::Token>& tokens);
            std::vector<ConfigServer>   parse(void);
    };
}

#endif