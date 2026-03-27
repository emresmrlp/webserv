/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 06:30:43 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/27 12:47:26 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//v0.1.0 version is only parse HTTP header
//connections is sockets

#ifndef CONNECTION_HPP
# define CONNECTION_HPP
# include <string>
# include <exception>
# include "RequestBuilder.hpp"
# include "ResponseFactory.hpp"
# include "ResponseDispatcher.hpp"

namespace http
{
	class Request;
	class IResponse;
}

namespace core
{
	enum ConnectionState
	{
		READING,
		WRITING,
		CLOSING
	};

	class Connection
	{
		public:
			Connection(int fd, core::Server &server);
			~Connection();

			void					process();
			bool					hasResponse() const;
			void					resetForNextRequest();
			void					appendRequestBuffer(const std::string &buffer);
			
			int						getFd() const;
			core::ConnectionState	getState() const;
			const std::string		&getResponseBuffer() const;

			void					setState(ConnectionState state);
		private:
			int							_fd;
			std::string					_readBuffer;
			std::string					_writeBuffer;
			http::IResponse				*_response;
			http::Request				*_request;
			http::ResponseDispatcher	_dispatcher;
			http::RequestBuilder		_requestBuilder;
			http::ResponseFactory		_responseFactory;
			core::ConnectionState		_state;
			core::Server				_server;
	};
}

#endif