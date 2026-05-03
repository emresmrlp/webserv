/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 19:39:19 by beldemir          #+#    #+#             */
/*   Updated: 2026/05/03 18:19:58 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/config/Parser.hpp"

namespace	config
{
	Parser::Parser(const std::vector<config::Token>& tokens) 
		: _tokens(tokens), _pos(0) {}

	config::Token	Parser::curr(void)
	{
		if (_pos >= _tokens.size())
			return (_tokens.back());
		return (_tokens[_pos]);
	}

	ConfigLocation  Parser::parseLocation(void)
	{
		ConfigLocation	loc;

		// Path assignment (e.g., "/")
		if (curr().getType() == VALUE)
		{
			loc.setExecutePath(curr().getStr());
			_pos++;
		}

		// Handle potential modifiers like "-" or "index" in your conf
		while (curr().getType() == VALUE)
			_pos++;
		// YUNUS'A SOR O "/ - index" KULLANIMI NE IFADE EDIYOR?

		if (curr().getType() != OPEN_BLOCK)
			return (loc); // ERROR: OPEN BLOCK YOK
		
		_pos++; // skip "{"

		while (curr().getType() != CLOSE_BLOCK && curr().getType() != END_OF_FILE)
		{
			if (curr().getType() == KEYWORD)
			{
				std::string key = curr().getStr();
				_pos++;
				
				if (key == "allowed_methods")
				{
					while (curr().getType() == VALUE)
					{
						loc.addAllowedMethod(curr().getStr());
						_pos++;
					}
				}
				else if (key == "root")
				{
					if (curr().getType() == VALUE)
					{
						loc.setRootPath(curr().getStr());
						_pos++;
					}
				}
				// Handle index, autoindex etc. here
			}
			if (curr().getType() == SEMICOLON)
				_pos++;
			else if (curr().getType() != CLOSE_BLOCK)
				_pos++; // Safeguard to prevent infinite loop
		}
		_pos++; // skip "}"
		return (loc);
	}
	
	ConfigServer    Parser::parseServer(void)
	{
		ConfigServer    server;

		if (curr().getType() != OPEN_BLOCK)
			return (server); // ERROR: OPEN BLOCK YOK
		_pos++;

		while (curr().getType() != CLOSE_BLOCK && curr().getType() != END_OF_FILE)
		{
			if (curr().getType() == KEYWORD)
			{
				std::string key = curr().getStr();
				_pos++;

				if (curr().getType() != VALUE)
					return ; // ERROR: 

				if (key == "location")
				{
					server.addLocation(parseLocation());
					continue ;
				}
				else if (key == "listen")
				{
					while (curr().getType() == VALUE)
					{
						// Logic for port/host/default_server extraction
						// e.g., server.setPort(atoi(curr().getStr().c_str()));
						_pos++;
					}
				}
				else if (key == "server_name")
				{
					while (curr().getType() == VALUE)
					{
						server.addServerName(curr().getStr());
						_pos++;
					}
				}
				else if (key == "root")
				{
					server.setRoot(curr().getStr());
					_pos++;
				}
			}
			if (curr().getType() == SEMICOLON)
				_pos++;
			else if (curr().getType() != CLOSE_BLOCK && curr().getType() != KEYWORD)
				_pos++;
		}
		_pos++; // skip "}"
		return (server);
	}

	std::vector<ConfigServer>   Parser::parse(void)
	{
		std::vector<ConfigServer> servers;

		_pos = 0;
		while (_pos < _tokens.size() && curr().getType() != END_OF_FILE)
		{
			if (curr().getType() == KEYWORD && curr().getStr() == "server")
			{
				_pos++;
				servers.push_back(parseServer());
			}
			else
				_pos++; // Skip anything not a server block at top level
		}
		return (servers);
	}
}