#include "Socket.hpp"

Socket::Socket(int domain, int service, int protocol, int port, u_long interface)
{
    addr.sin_family = domain;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(interface);
    sockfd = socket(domain, service, protocol);
    //test_connection(sockfd);
    connectfd = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    //test_connection(connectfd);
     
}
Socket::~Socket()
{
    close(sockfd);
    close(connectfd);
}

void    Socket::test_connection(int fd)
{
    if (fd < 0)
    {
        throw Suck_it();
        exit(1);
    }
}

int    Socket::getSockfd()
{
    return sockfd;
}

int    Socket::getConnectfd()
{
    return connectfd;
}

struct sockaddr_in Socket::getAddr()
{
    return addr;
}