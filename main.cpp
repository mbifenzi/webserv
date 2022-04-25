#include "Socket.hpp"
#include "Response.hpp"
#include "Request.hpp"

int main()
{
    try
    {
        Socket sock(AF_INET, SOCK_STREAM, 0, 1415, INADDR_ANY);
        Request req;
        while (1)
        {
            if (listen(sock.getSockfd(), 10) < 0) 
            {
                std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
                exit(1);
            }
            int connfd = accept(sock.getSockfd(), (struct sockaddr *)NULL, NULL);
            char buffer[1024];
            int n = read(connfd, buffer, 1024);
            buffer[n] = '\0';
            std::cout << buffer << std::endl;
            req.getHeader(buffer);
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