/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 06:30:43 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/18 09:21:55 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//v0.1.0 version is only parse HTTP header
//connections is sockets

#ifndef CONNECTION_H
# define CONNECTION_H
# include <string>
# include "HTTPRequest.hpp"

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

		HTTPRequest		&getRequest(); //TODO: test case, we need to delete this
		void			update();
		int				getFd() const;
		void			setState(ConnectionState state);
		ConnectionState getState() const;
		// & referance for server - edit the writeBuffer
		std::string		&getWriteBuffer();
		void			addReadBuffer(const std::string &buffer);
	private:
		// private for data security reasons
		std::string		&getReadBuffer(); // TODO: can we really need to read-write readBuffer on this method?
		Connection();
		Connection(const Connection &ref);
		Connection &operator=(const Connection &ref);

		int				_fd;
		ConnectionState	_state;
		std::string		_readBuffer;
		std::string		_writeBuffer;
		HTTPRequest		_request;
};

#endif