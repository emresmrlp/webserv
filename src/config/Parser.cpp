/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 19:39:19 by beldemir          #+#    #+#             */
/*   Updated: 2026/06/10 12:45:49 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include "ConfigServerBuilder.hpp"
#include "ConfigLocationBuilder.hpp"

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

	ConfigLocation	Parser::parseLocation(void)
	{
		ConfigLocationBuilder	locationBuilder;

		if (isType(VALUE) && thisStr()[0] == '/')
			locationBuilder.setExecutePath(thisStr()), next();
		else
			throw std::runtime_error(EXPECTED_PATH);

		if (!isType(OPEN_BLOCK))
			throw std::runtime_error(EXPECTED_OPEN_BLOCK);

		next();

		while (!isType(CLOSE_BLOCK) && !isType(END_OF_FILE))
		{
			if (isType(KEYWORD))
			{
				std::string	key = thisStr();
				next();

				if (!isType(VALUE))
					throw std::runtime_error(EXPECTED_VALUE);

				if (key == "allowed_methods")
					while (isType(VALUE))
						locationBuilder.addAllowedMethod(thisStr()), next();
				else if (key == "index")
					while (isType(VALUE))
						locationBuilder.addToIndexList(thisStr()), next();
				else if (key == "root")
					locationBuilder.setRootPath(thisStr()), next();
				else if (key == "upload_store")
					locationBuilder.setUploadPath(thisStr()), next();
				else if (key == "autoindex")
					locationBuilder.setAutoIndex(thisStr()), next();
				else if (key == "client_max_header_size")
					locationBuilder.setMaxHeaderSize(thisStr()), next();
				else if (key == "client_max_body_size")
					locationBuilder.setMaxBodySize(thisStr()), next();
				else if (key == "return")
				{
					int	code = atoi(thisStr().c_str());
					next();
					locationBuilder.setReturnRedirection(code, thisStr()), next();
				}
				else if (key == "cgi_pass")
				{
					std::string	ext = thisStr();
					next();
					locationBuilder.addCgiPass(ext, thisStr()), next();
				}
			}
			if (isType(SEMICOLON))
				next();
			else if (!isType(CLOSE_BLOCK))
				next();
		}
		next();
		return (locationBuilder.build());
	}
	
	ConfigServer    Parser::parseServer(void)
	{
		ConfigServerBuilder	serverBuilder;

		if (!isType(OPEN_BLOCK))
			throw std::runtime_error(EXPECTED_OPEN_BLOCK);

		next();

		while (!isType(CLOSE_BLOCK) && !isType(END_OF_FILE))
		{
			if (isType(KEYWORD))
			{
				std::string key = thisStr();
				next();

				if (!isType(VALUE))
					throw std::runtime_error(EXPECTED_VALUE);

				if (key == "location")
				{
					serverBuilder.addLocation(parseLocation());
					continue ;
				}
				else if (key == "listen")
					while (isType(VALUE))
						(serverBuilder.addListen(thisStr()), next());
				else if (key == "server_name")
					while (isType(VALUE))
						serverBuilder.addServerName(thisStr()), next();
				else if (key == "root")
					serverBuilder.setRoot(thisStr()), next();
				else if (key == "client_max_header_size")
					serverBuilder.setMaxHeaderSize(thisStr()), next();
				else if (key == "client_max_body_size")
					serverBuilder.setMaxBodySize(thisStr()), next();
				else if (key == "http_version")
					serverBuilder.setHttpVersion(thisStr()), next();
				else if (key == "error_page")
				{
					std::string	errorNo = thisStr();
					next();
					serverBuilder.addErrorPage(errorNo, thisStr()), next();
				}
			}
			else
				throw std::runtime_error(EXPECTED_VALUE);

			if (isType(SEMICOLON))
				next();
			else if (!isType(CLOSE_BLOCK))
				next();
		}
		next();
		return (serverBuilder.build());
	}

	void	Parser::parse(void)
	{
		try
		{
			_tokens = tokenize(_filename);
			if (_tokens.empty())
				throw std::invalid_argument("No tokens in file");
			_pos = 0;
			while (!isType(END_OF_FILE) && _pos < _tokens.size())
			{
				if (isType(KEYWORD) && thisStr() == "server")
				{
					next();
					_servers.push_back(parseServer());
					if (PARSER_DEBUG_MODE)
						_servers.at(_servers.size() - 1).print();
				}
				else
					next();
			}
		}
		catch (std::exception &e)
		{
			std::ostringstream	errMsg;
			if (_tokens.empty())
				errMsg << "check file: " << e.what();
			else
				errMsg << "on line " << thisLine() << ": " << e.what();

			throw std::invalid_argument(errMsg.str());
		}
	}

	const	std::vector<ConfigServer>&	Parser::getServers() const { return (_servers); }
}
