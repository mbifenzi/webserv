#ifndef SOCKET_HPP
#define SOCKET_HPP
#include <string>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
class Socket
{
	private:
		int sockfd;
	public:	
		socket(int domain, int type, int protocol);
};

#endif