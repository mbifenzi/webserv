#include "Socket.hpp"


Socket::Socket(int domain, int service, int protocol, int port, u_long interface)
{
    struct sockaddr_in address;
    //fds = std::vector<struct pollfd>(1);
    address.sin_family = domain;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = interface;

    sockfd = socket(domain, service, protocol);
    if (sockfd < 0)
        perror("socket error ");

    fcntl( sockfd, F_SETFL, O_NONBLOCK);
    bindfd = bind(sockfd, (struct sockaddr *) &address, sizeof(address));
    if (bindfd < 0)
    {
        throw "cannot bind\n";
    }
    int l = listen(sockfd, 1000);
    if (l < 0)
        perror("listen error");
}
Socket::~Socket()
{
    // close(sockfd);
    // close(connectfd);
}
Socket &Socket::operator=(const Socket &sock)
{
    this->sockfd = sock.sockfd;
    this->bindfd = sock.bindfd;
    this->addr = sock.addr;
    return *this;
}

int    Socket::getSockfd()
{
    return sockfd;
}
