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
#include <fcntl.h>
#include "Response.hpp"
#include "Request.hpp"
#include <poll.h>
// #include <string>
class Socket
{
	private:
		int sockfd;
		int bindfd;
		int connectfd;
		std::vector<struct pollfd> fds;
		struct sockaddr_in addr;
	public:
		Socket(int domain, int service, int protocol, int port, u_long interface);
		~Socket();
		int 	getSockfd();
		int 	getConnectfd();
		void	setConnectfd(int connectfd);
		void	addFd(struct pollfd fd);
		void	removeFd(int index);
		void	setFds(std::vector<struct pollfd> fds);
		void	event_loop();
		std::vector<struct pollfd> getFds();
		struct sockaddr_in getAddr();
		class Suck_it:public std::exception
    	{
			const char* what() const throw()
			{
				return "socket() failed";
			}
    	};
};

#endif