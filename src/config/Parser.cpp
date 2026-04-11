/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 19:39:19 by beldemir          #+#    #+#             */
/*   Updated: 2026/04/11 21:00:57 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/config/Parser.hpp"

namespace	config
{
	Parser::Parser()
		: _tokens(config::Tokenize("../../conf/default.conf")), _pos(0) { }

	Parser::Parser(const Parser& other)
		: _tokens(other.getTokens()), _pos(0) { }

	Parser&	Parser::operator=(const Parser& other) {
		//this->_tokens = other.getTokens();
		this->_pos = 0;
	}
} 