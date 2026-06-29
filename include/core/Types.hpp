#ifndef TYPES_HPP
# define TYPES_HPP
# include <netinet/in.h>

namespace core
{	
	struct HostAddr
	{
		in_addr_t	ip;
		uint16_t	port;

		bool operator==(const HostAddr& ref) const
		{
        	return (this->ip == ref.ip) && (this->port == ref.port);
		}
	};
}

#endif