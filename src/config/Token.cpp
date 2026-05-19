/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:06:11 by ysumeral          #+#    #+#             */
/*   Updated: 2026/05/19 14:15:57 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/config/Token.hpp"

namespace config
{
	Token::Token()
		: _type(END_OF_FILE), _str(""), _line(0) { }

	Token::Token(const Token& other)
		: _type(other.getType()), _str(other.getStr()), _line(other.getLine()) { }
		
	Token&	Token::operator=(const Token& other) {
		this->_type = other.getType();
		this->_str = other.getStr();
		this->_line = other.getLine();
		return (*this);
	}

	Token::~Token() { }

	Token::Token(TokenType type, std::string str, size_t line)
		: _type(type), _str(str), _line(line) { }

	TokenType	Token::getType(void) const { return (this->_type); }
	std::string	Token::getStr(void) const { return (this->_str); }
	size_t		Token::getLine(void) const { return (this->_line); } 

	////////////////////////////////////////////////////////////////////////////

	bool	isKeyword(std::string str)
	{
		static const std::string keywords[] = {
			"server",
			"location",
			"listen",
			"root",
			"index", 
			"error_page",
			"client_max_body_size",
			"autoindex",
			"allowed_methods",
			"server_name",
		};

		size_t	numKeywords = sizeof(keywords) / sizeof(keywords[0]);

		for (size_t i = 0; i < numKeywords; ++i)
		{
			if (str == keywords[i])
				return true;
		}

		return false;
	}

	std::vector<Token>	tokenize(std::string filename)
	{
		std::vector<Token>	tokens;
		std::string			line;
		std::ifstream		file(filename.c_str());
		std::string			content;
		bool				expecting = true;
		size_t				currLine;
		size_t				i;
		
		if (!file.is_open())
			return tokens;
		
		while (std::getline(file, line))
			content += line + "\n";

		i = 0;
		currLine = 1;
		while (i < content.length())
		{
			if (content[i] == '\n' && ++currLine)
				i++;
			else if (isspace(content[i]))
				i++;
			else if (content[i] == '#')
				while (i < content.length() && content[i] != '\n')
					i++;
			else if (content[i] == '{' && (expecting = true) && ++i)
				tokens.push_back(Token(OPEN_BLOCK, "{", currLine));
			else if (content[i] == '}' && (expecting = true) && ++i)
				tokens.push_back(Token(CLOSE_BLOCK, "}", currLine));
			else if (content[i] == ';' && (expecting = true) && ++i)
				tokens.push_back(Token(SEMICOLON, ";", currLine));
			else
			{
				size_t	start = i;
				while (i < content.length() && !isspace(content[i]) && content[i] != '\n'
					&& content[i] != '{' && content[i] != '}' && content[i] != ';')
					i++;
				std::string word = content.substr(start, i - start);
				if (expecting && isKeyword(word))
					tokens.push_back(Token(KEYWORD, word, currLine));
				else if (expecting)
				{
					std::cerr << "Error at line " << currLine << " : Expected a keyword but you gave " << word << "." << std::endl;
					return std::vector<Token>();
				}
				else
					tokens.push_back(Token(VALUE, word, currLine));
				expecting = false;
			}
		}
		tokens.push_back(Token(END_OF_FILE, "",currLine));
		return (tokens);
	}
}
