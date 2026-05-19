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
# include <vector>
# include <string>
# include <cstdlib>

namespace	config
{
	class	Parser
	{
		private:
			std::string							_filename;
			std::vector<config::Token>			_tokens;
			size_t								_pos;
			ConfigLocation						_locationBuffer;
			ConfigServer						_serverBuffer;
			std::vector<ConfigServer>			_servers;

			config::TokenType	thisType(void)					const;
			std::string			thisStr(void)					const;
			int					thisLine(void)					const;

			bool				isStr(std::string str)			const;
			bool				isType(config::TokenType type)	const;

			void				next(void);

			bool				parseServer(void);
			bool				parseLocation(void);

		public:
			Parser(std::string filename);
			bool	parse(void);
	};
}

#endif