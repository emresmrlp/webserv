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

	bool	isKeyword(std::string str)
	{
		static const std::string keywords[] = {
			"server",
			"location",
			"listen",
			"root",
			"index", 
			"error_page",
			"client_max_header_size",
			"client_max_body_size",
			"autoindex",
			"allowed_methods",
			"server_name",
			"return",
			"cgi_pass",
			"upload_store",
			"http_version"
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
		std::string ext = ".conf";
		if (filename.length() < ext.length() || 
			filename.compare(filename.length() - ext.length(), ext.length(), ext) != 0)
			throw std::invalid_argument("Filename must end with .conf");

		struct stat path_stat;
		if (stat(filename.c_str(), &path_stat) != 0)
			throw std::invalid_argument(filename + "does not exist or path is invalid");
		if (S_ISDIR(path_stat.st_mode))
			throw std::invalid_argument(filename + " is a directory, not a file");

		std::ifstream	file(filename.c_str());
		if (!file.is_open())
			throw std::invalid_argument("Failed to open file");

		std::vector<Token>	tokens;
		std::string			line;
		std::string			content;
		bool				expecting = true;
		size_t				currLine = 1;
		size_t				i = 0;

		if (!file.is_open())
			throw std::invalid_argument("File is not reachable");

		while (std::getline(file, line))
			content += line + "\n";

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
					throw std::invalid_argument("Expected a keyword");
				else
					tokens.push_back(Token(VALUE, word, currLine));
				expecting = false;
			}
		}
		tokens.push_back(Token(END_OF_FILE, "",currLine));
		return (tokens);
	}
}
