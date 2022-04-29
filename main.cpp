#include "Socket.hpp"
#include "Response.hpp"
#include "Request.hpp"
#include <fcntl.h>
#include <poll.h>
int main()
{
    try
    {
        Socket sock(AF_INET, SOCK_STREAM, 0, 1415, INADDR_ANY);
        Request req;
        int n;
// if (listen(sock.getSockfd(), 128) < 0) 
//     {
//         std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
//         exit(1);
        while (1)
        {
            if (listen(sock.getSockfd(), 128) < 0) 
            {
                std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
                exit(1);
            }
            // fcntl(sock.getSockfd(), F_SETFL, O_NONBLOCK);
            int connfd = accept(sock.getSockfd(), (struct sockaddr *)NULL, NULL);
            // fcntl(connfd, F_SETFL, O_NONBLOCK);
            if (connfd < 0)
            {
                std::cout << "Failed to accept connection. errno: " << errno << std::endl;
                continue;
            }
            char buffer[1024];
            n = read(connfd, buffer, 1024);
            buffer[n] = '\0';
            // std::cout << "buffer: " << buffer << std::endl;
            //intilaize the request with buffer and n
            std::string request(buffer, n);
            // std::cout << "debug: " << std::endl;
            // std::cout << "request: " << request << std::endl;
            req.getHeader(request);
            // std::cout << request << std::endl;
            char msg[] ="HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 24\n\nHello world from server!";
            write(connfd, msg, strlen(msg));
            close(connfd);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}