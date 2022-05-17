#include "Socket.hpp"


Socket::Socket(int domain, int service, int protocol, int port, u_long interface)
{
    fds = 		 std::vector<struct pollfd>(1);
    addr.sin_family = domain;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(interface);
    sockfd = socket(domain, service, protocol);
    bindfd = bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
    if (bindfd < 0)
    {
        throw "cannot bind\n";
    }
    fcntl( sockfd, F_SETFL, O_NONBLOCK);
    listen(sockfd, 10);
}
Socket::~Socket()
{
    close(sockfd);
    // close(connectfd);
}

int    Socket::getSockfd()
{
    return sockfd;
}

void Socket::initFd()
{
    fds = std::vector<fd_t>(1);
    fds[0].fd = sockfd;
    fds[0].events = POLLIN;

}

void Socket::addFd()
{
    fds.push_back(fd_t());
    fds[fds.size() - 1].fd = sockfd;
    fds[fds.size() - 1].events = POLLIN;
}



// int    Socket::getConnectfd()
// {
//     return connectfd;
// }

struct sockaddr_in Socket::getAddr()
{
    return addr;
}

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

