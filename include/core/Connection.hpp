/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 06:30:43 by ysumeral          #+#    #+#             */
/*   Updated: 2026/06/25 11:15:49 by ysumeral         ###   ########.fr       */
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
		TIMEOUT,
		READING,
		WRITING,
		CLOSING
	};

	class Connection
	{
		public:
			Connection(int fd);
			~Connection();

			void					handleTimeout();
			void					process();
			bool					hasResponse() const;
			void					resetForNextRequest();
			void					appendRequestBuffer(const std::string &buffer);
			void 					eraseResponseBuffer(std::size_t bytesSent);
			
			int						getFd() const;
			core::ConnectionState	getState() const;
			const std::string		&getResponseBuffer() const;
			std::size_t				getSentBytes() const;

			void					setState(ConnectionState state);
			void					setConfig(const config::ConfigServer *config);
		private:
			int							_fd;
			std::string					_readBuffer;
			std::string					_writeBuffer;

			http::IResponse				*_response;
			http::Request				*_request;

			http::ResponseFactory		_responseFactory;
			http::ResponseDispatcher	_dispatcher;
			http::RequestBuilder		_requestBuilder;

			core::ConnectionState		_state;
			std::size_t					_sentBytes;

			const config::ConfigServer	*_config;
	};
}

#endif