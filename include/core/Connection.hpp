/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 06:30:43 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/18 22:04:51 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//v0.1.0 version is only parse HTTP header
//connections is sockets

#ifndef CONNECTION_HPP
# define CONNECTION_HPP
# include <string>
# include "Request.hpp"
# include "AResponseBase.hpp"
# include <exception>
//every connection object is a socket so connection state is equal socket state
enum ConnectionState
{
	//socket reading,
	//socket writing (http request + http response + server send)
	//connection closing (server send process ending)
	READING,
	WRITING,
	ERROR,
	CLOSING
};

class Connection
{
	public:
		Connection(int fd);
		~Connection();

		Request			&getRequest(); //TODO: test case, we need to delete this
		void			update();
		int				getFd() const;
		void			setState(ConnectionState state);
		ConnectionState getState() const;
		void			handleRequest(StatusCode status);
		IResponse		*getResponse();
		void			addReadBuffer(const std::string &buffer);
		class NoResponseFoundError : public std::exception
		{
			public:
				const char *what() const throw();
		};
	private:
		int				_fd;
		ConnectionState	_state;
		IResponse		*_response;
		std::string		_readBuffer;
		std::string		_writeBuffer;
		Request			_request; // TODO: delete this after tests
};

#endif