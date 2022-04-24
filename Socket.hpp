#ifndef SOCKET_HPP
#define SOCKET_HPP
#include <string>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <vector>
#include <map>
#include <sstream>
// #include <string>
class Socket
{
	private:
		int sockfd;
		int connectfd;
		struct sockaddr_in addr;
	public:
		Socket(int domain, int service, int protocol, int port, u_long interface);
		~Socket();
		int 	getSockfd();
		int 	getConnectfd();
		struct sockaddr_in getAddr();
		void	test_connection(int fd);
		// virtual int connect_to_server(int sockfd, struct sockaddr_in addr);
		class Suck_it:public std::exception
    	{
			const char* what() const throw()
			{
				return "socket() failed";
			}
    	};
};

#endif