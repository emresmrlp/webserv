/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 19:39:19 by beldemir          #+#    #+#             */
/*   Updated: 2026/05/19 16:59:09 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/config/Parser.hpp"

namespace	config
{
	Parser::Parser(std::string filename) 
		: _filename(filename), _pos(0) {}

	config::TokenType	Parser::thisType(void)		const
	{
		if (_pos >= _tokens.size())	return (_tokens.back().getType());
		else						return (_tokens[_pos].getType());
	}

	std::string	Parser::thisStr(void)				const
	{
		if (_pos >= _tokens.size())	return (_tokens.back().getStr());
		else 						return (_tokens[_pos].getStr());
	}

	int	Parser::thisLine(void)				const
	{
		if (_pos >= _tokens.size())	return (_tokens.back().getLine());
		else 						return (_tokens[_pos].getLine());
	}

	bool	Parser::isStr(std::string	str)		const
	{
		if (thisStr() == str)	return (true);
		else					return (false);
	}

	bool	Parser::isType(config::TokenType type)	const
	{
		if (thisType() == type)	return (true);
		else					return (false);
	}

	void	Parser::next(void) { if (_pos < _tokens.size()) _pos++; }

	bool  Parser::parseLocation(void)
	{
		ConfigLocation	loc;

		if (isType(VALUE) || thisStr()[0] == '/')
			loc.setExecutePath(thisStr()), next();
		else
			return (false);

		if (!isType(OPEN_BLOCK))
			return (false);

		next();

		while (!isType(CLOSE_BLOCK) && !isType(END_OF_FILE))
		{
			if (isType(KEYWORD))
			{
				std::string	key = thisStr();
				next();

				if (!isType(VALUE))
					return (false);

				if (key == "allowed_methods")
					while (isType(VALUE))
						loc.addAllowedMethod(thisStr()), next();
				else if (key == "root")
					loc.setRootPath(thisStr()), next();
				else if (key == "autoindex")
				{
					if (!loc.setAutoIndex(thisStr()))
						return (false);
					next();
				}
			}
			if (isType(SEMICOLON))
				next();
			else if (!isType(CLOSE_BLOCK))
				next();
		}
		next();
		_locationBuffer = loc;
		return (true);
	}
	
	bool    Parser::parseServer(void)
	{
		ConfigServer    server;

		if (!isType(OPEN_BLOCK))
			return (false);

		next();

		while (!isType(CLOSE_BLOCK) && !isType(END_OF_FILE))
		{
			if (isType(KEYWORD))
			{
				std::string key = thisStr();
				next();

				if (!isType(VALUE))
					return (false);

				if (key == "location")
				{
					if (!parseLocation())
						return (false);
					server.addLocation(_locationBuffer);
					continue ;
				}
				else if (key == "listen")
				{
					while (isType(VALUE))
					{
						if (!server.addListen(thisStr()))
							return (false);
						next();
					}
				}
				else if (key == "server_name")
					while (isType(VALUE))
						server.addServerName(thisStr()), next();
				else if (key == "root")
					server.setRoot(thisStr()), next();
				else if (key == "error_page")
				{
					std::string	errorNo = thisStr();
					next();
					if (!server.addErrorPage(errorNo, thisStr()))
						return (false);
					next();
				}
				else if (key == "client_max_header_size")
				{
					if (!server.setMaxHeaderSize(thisStr()))
						return (false);
					next();
				}
				else if (key == "client_max_body_size")
				{
					if (!server.setMaxBodySize(thisStr()))
						return (false);
					next();
				}
			}
			else
				return (false);

			if (isType(SEMICOLON))
				next();
			else if (!isType(CLOSE_BLOCK))
				next();
		}
		next();
		_serverBuffer = server;
		return (true);
	}

	bool	Parser::parse(void)
	{
		_tokens = tokenize(_filename);
		if (_tokens.empty())
			return (false);
		_pos = 0;
		while (!isType(END_OF_FILE) && _pos < _tokens.size())
		{
			if (isType(KEYWORD) && thisStr() == "server")
			{
				next();
				if (!parseServer())
				{
					std::cerr << "Error at line " << thisLine() << ": couldn't parse it." << std::endl;
					return (false);
				}
				_serverBuffer.print();
				_servers.push_back(_serverBuffer);
			}
			else
				next();
		}
		return (true);
	}
}
