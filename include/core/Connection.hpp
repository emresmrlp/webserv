/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 06:30:43 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/18 16:55:33 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//v0.1.0 version is only parse HTTP header
//connections is sockets

#ifndef CONNECTION_HPP
# define CONNECTION_HPP
# include <string>
# include "Request.hpp"
# include "AResponseBase.hpp"

//every connection object is a socket so connection state is equal socket state
enum ConnectionState
{
	//socket reading,
	//socket writing (http request + http response + server send)
	//connection closing (server send process ending)
	READING,
	WRITING,
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
	private:
		// private for data security reasons
		std::string		&getReadBuffer(); // TODO: can we really need to read-write readBuffer on this method?
		Connection();

		int				_fd; // server
		ConnectionState	_state;
		IResponse		*_response;
		std::string		_readBuffer; //server
		std::string		_writeBuffer;
		Request			_request; // TODO: delete this after tests
};

#endif