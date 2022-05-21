#include "Socket.hpp"


Socket::Socket(int domain, int service, int protocol, int port, u_long interface)
{
    struct sockaddr_in address;
    //fds = std::vector<struct pollfd>(1);
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = interface;

    sockfd = socket(domain, service, protocol);
    if (sockfd < 0)
        perror("SOkcet ");

    fcntl( sockfd, F_SETFL, O_NONBLOCK);
    bindfd = bind(sockfd, (struct sockaddr *) &address, sizeof(address));
    if (bindfd < 0)
    {
        throw "cannot bind\n";
    }
    int l = listen(sockfd, 1000);
    if (l < 0)
        perror("Ta9 ta9");
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
    // this->fds = sock.fds;
    return *this;
}

int    Socket::getSockfd()
{
    return sockfd;
}






// int    Socket::getConnectfd()
// {
//     return connectfd;
// }

// struct sockaddr_in Socket::getAddr()
// {
//     return addr;
// }

// void Socket::setConnectfd(int connectfd)
// {
//     this->connectfd = connectfd;
// }

// void Socket::removeFd(int index)
// {
//     fds.erase(fds.begin() + index);
// }

// void Socket::setFds(std::vector<struct pollfd> fds)
// {
//     this->fds = fds;
// }
