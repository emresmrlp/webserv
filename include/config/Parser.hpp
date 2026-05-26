/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 19:39:23 by beldemir          #+#    #+#             */
/*   Updated: 2026/05/19 13:24:52 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include "Token.hpp"
# include "ConfigServer.hpp"
# include "ConfigLocation.hpp"
# include <vector>
# include <string>
# include <exception>
# include <cstdlib>
# include <sstream>

# define EXPECTED_OPEN_BLOCK "Expected {"
# define EXPECTED_VALUE "Expected a value"
# define EXPECTED_PATH "Expected a path starting with '/'"

# define PARSER_DEBUG_MODE false // !!delete

namespace	config
{
	class	Parser
	{
		private:
			std::string							_filename;
			std::vector<config::Token>			_tokens;
			size_t								_pos;
			std::vector<ConfigServer>			_servers;

			config::TokenType	thisType(void)					const;
			std::string			thisStr(void)					const;
			int					thisLine(void)					const;

			bool				isStr(std::string str)			const;
			bool				isType(config::TokenType type)	const;

			void				next(void);

			ConfigServer		parseServer(void);
			ConfigLocation		parseLocation(void);

		public:
			Parser(std::string filename);
			void	parse(void);

			const std::vector<ConfigServer>&	getServers()	const;
	};
}

#endif