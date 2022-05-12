#include "Socket.hpp"
#include "Response.hpp"
#include "Request.hpp"
#include <fcntl.h>
#include <poll.h>
#include <vector>
// void accept_client(Socket* sock)
// {
//     int clientfd = accept(sock->getSockfd(), NULL, NULL);
//     if (clientfd < 0)
//     {
//         throw "cannot accept\n";
//     }
//     fcntl(clientfd, F_SETFL, O_NONBLOCK);
//     sock->setConnectfd(clientfd);
// }
// void read_from_socket(int sockfd, std::string &buffer)
// {

// }


int main(int argc, char **argv)
{
    (void)argc;
    Socket socket(AF_INET, SOCK_STREAM, 0, atoi(argv[1]), INADDR_ANY);
    Request request;
    struct sockaddr_in address;
    // Response response;
    char buffer[1024];
    struct  pollfd fds[100];
    int new_connection;
    int nfds;
    int n = 0;
    int address_len = sizeof(address);
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    fds[0].fd = socket.getSockfd();
    fds[0].events = POLLIN;
    int polling_happened = fds[0].revents & POLLIN;
    if (polling_happened == 0)
    {
        std::cout << "No polling happened 11" << std::endl;
    }
    if (polling_happened)
    {
        std::cout << "Polling happened 11" << std::endl;
    }
    nfds = 1;
    int index = 0;
    while (1)
    {
        int ret = poll(fds, nfds, -1);
        // std::cout << "debug" << std::endl;
        if (ret == 0)
        {
            std::cout << "poll timeout" << std::endl;
            continue ;
        }
        for (int i = 0; i < nfds ; i++)
        {
            int polling_happened = fds[i].revents & POLLIN;
            if (!polling_happened)
            {
                std::cout << "No polling happened" << i << std::endl;
            }
            else if (polling_happened)
            {
                // read from socket
                // read_from_socket(fds[i].fd, buffer);
                std::cout << "Polling happened" << i << std::endl;
                if (fds[i].fd == socket.getSockfd())
                {
                    std::cout << "connection to accept " << std::endl;
                    new_connection = accept(socket.getSockfd(), (struct sockaddr *)&address,(socklen_t *)&address_len);
                    fcntl(new_connection, F_SETFL, O_NONBLOCK);
                    fds[nfds].fd = new_connection;
                    fds[nfds].events = POLLIN;
                    nfds++;
                    continue;
                }
                else
                {
                    std::cout << "message to read " << std::endl;
                    n = read( fds[i].fd, buffer, 1024);
                    if (n == 0)
                    {
                        std::cout << "Connection closed" << std::endl;
                        close(fds[i].fd);
                        continue;
                    }
                    // buffer[n] = '\0';
                    std::cout << "you are able to send data " << std::endl;
                    write(1, buffer , n);
                    fds[i].events = POLLOUT;
                    char msg[] ="HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 24\n\nHello world from server!";
                    write(1, msg, strlen(msg));
                    close(fds[i].fd);
                    nfds--;
                    fds[i].fd = -1;
                    fds[i].events = 0;
                    fds[i].revents = 0;
                }
                    
                    // continue;
            }
        }
    }
}