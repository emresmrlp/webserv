#ifndef TYPES_HPP
# define TYPES_HPP
# include <netinet/in.h>

namespace core
{	
	struct HostAddr
	{
		in_addr_t	ip; // ? in_addr_t typedef for uint32_t (internet address type)
		uint16_t	port;

		bool operator==(const HostAddr& ref) const // ? overloading for comparing HostAddr objects
		{
        	return (this->ip == ref.ip) && (this->port == ref.port);
		}
	};
}

#endif