#include "Socket.hpp"
#include "Response.hpp"
#include "Request.hpp"
#include <fcntl.h>
#include <poll.h>

int main()
{
    Socket socket(AF_INET, SOCK_STREAM, 0, 1415, INADDR_ANY);
    Request request;
    // Response response;
    struct  pollfd fds[10];
    int n;
    int i = 0;
    while (1)
    {
        if (listen(socket.getSockfd(), 128) < 0) 
        {
            std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
            exit(1);
        }
        fds[i].fd = socket.getSockfd();
        fds[i].events = POLLIN;
        i++;
        int connfd = accept(socket.getSockfd(), (struct sockaddr *)NULL, NULL);
        if (connfd < 0)
        {
            std::cout << "Failed to accept connection. errno: " << errno << std::endl;
            continue;
        }
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        n = read(connfd, buffer, sizeof(buffer));
        std::string request(buffer, n);
        
}