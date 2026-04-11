/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 19:39:23 by beldemir          #+#    #+#             */
/*   Updated: 2026/04/11 19:49:08 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Token.hpp"

namespace	config
{
	class	Parser
	{
		private:
			const	std::vector<Token>&	_tokens;
			size_t	_pos;
		public:
			Parser(); // uses the default.conf file in ../../conf/default.conf
			Parser(const Parser& other);
			Parser&	operator=(const Parser& other);
			~Parser();

			Parser(std::string filename);

			std::vector<Token>	getTokens(void) const;
	};
}