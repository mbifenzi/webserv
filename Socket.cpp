#include "Socket.hpp"

Socket::Socket(int domain, int service, int protocol, int port, u_long interface)
{
    addr.sin_family = domain;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(interface);
    sockfd = socket(domain, service, protocol);
    connectfd = bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
    fcntl( sockfd, F_SETFL, O_NONBLOCK);
    listen(sockfd, 10);
     
}
Socket::~Socket()
{
    close(sockfd);
    close(connectfd);
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