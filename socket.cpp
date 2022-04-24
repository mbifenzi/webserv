#include "Socket.hpp"

Socket::Socket(int domain, int service, int protocol, int port, u_long interface)
{
    addr.sin_family = domain;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(interface);
    sockfd = socket(domain, service, protocol);
    test_connection(sockfd);
    connectfd = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    test_connection(connectfd);
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
// request parsing here ;
Request::Request()
{
    method = "";
    path = "";
    version = "";
    Header = std::map<std::string, std::string>();
    body = "";
    host = "";
    port = "";
}

Request::~Request()
{
}

Request::Request(std::string request)
{
    std::stringstream ss(request);
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(ss, line))
    {
        lines.push_back(line);
    }
    method = lines[0];
    path = lines[1];
    version = lines[2];
    for (int i = 3; i < lines.size(); i++)
    {
        std::stringstream ss(lines[i]);
        std::string key;
        std::string value;
        std::getline(ss, key, ':');
        std::getline(ss, value);
        Header[key] = value;
    }
    body = "";
    host = "";
    port = "";
}


