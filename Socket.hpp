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
// #include "Response.hpp"
// #include "Request.hpp"
#include <poll.h>
// #include <string>
class Socket
{
	private:
		int sockfd;
		int bindfd;
		// int connectfd;
		typedef struct pollfd fd_t;
		struct sockaddr_in addr;
	public:
		 std::vector<fd_t> fds;
		Socket(int domain, int service, int protocol, int port, u_long interface);
		~Socket();
		int 	getSockfd();
		int 	getConnectfd();
		void	setConnectfd(int connectfd);
		void 	addFd();
		void	initFd();
		void	removeFd(int index);
		void	setFds(std::vector<struct pollfd> fds);
		void	event_loop();
		Socket &operator=(const Socket &sock);
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