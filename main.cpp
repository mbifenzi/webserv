#include "Socket.hpp"

int main()
{
    try
    {
        Socket sock(AF_INET, SOCK_STREAM, 0, 1415, INADDR_ANY);
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
            //send data
            // char msg[] ="hayhayhay 3la t9e7biin\n";
            char msg[] ="HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
            write(connfd, msg, strlen(msg));
            close(connfd);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}