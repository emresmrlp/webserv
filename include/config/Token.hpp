/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:06:11 by ysumeral          #+#    #+#             */
/*   Updated: 2026/05/03 16:15:48 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_HPP
# define TOKENIZE_HPP
# include <iostream>
# include <vector>
# include <fstream>
# include <sstream>

namespace config
{
	typedef enum	E_TokenType
	{
		OPEN_BLOCK,
		CLOSE_BLOCK,
		SEMICOLON,
		KEYWORD,
		VALUE,
		COMMENT,
		END_OF_FILE
	}	TokenType;

	class	Token
	{
		private:
			TokenType	_type;
			std::string	_str;
			size_t		_line;

		public:
			Token();
			Token(const Token& other);
			Token&	operator=(const Token& other);
			~Token();

			Token(TokenType type, std::string str, size_t line);

			TokenType	getType(void) const;
			std::string	getStr(void) const;
			size_t		getLine(void) const;
	};

	bool						isKeyword(std::string str);
	std::vector<config::Token>	Tokenize(std::string filename);
}

#endif
