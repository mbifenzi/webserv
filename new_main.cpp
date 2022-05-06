#include "Socket.hpp"
#include "Response.hpp"
#include "Request.hpp"
#include <fcntl.h>
#include <poll.h>

int main(int argc, char **argv)
{
    (void)argc;
    Socket socket(AF_INET, SOCK_STREAM, 0, atoi(argv[1]), INADDR_ANY);
    //Request request;
     struct sockaddr_in address;
    // Response response;
    char buffer[1024];
    struct  pollfd fds[100];
    int new_connection;
    int nfds;
    int n;
    //int i = 0;
    int address_len = sizeof(address);
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    fds[0].fd = socket.getSockfd();
    fds[0].events = POLLIN;
    nfds = 1;
    while (1)
    {
        nfds = poll(fds, nfds, -1);
        for (int i = 0; i < nfds ; ++i)
        {
            if (fds[i].revents & POLLIN)
            {
                if (fds[i].fd == socket.getSockfd())
                {
                    new_connection = accept(socket.getSockfd(), (struct sockaddr *)&address,(socklen_t *)&address_len);
                    fcntl( new_connection, F_SETFL, O_NONBLOCK);
                    nfds++;
                    fds[nfds].fd = new_connection;
                    fds[nfds].events = POLLIN;
                    continue;
                }
                else
                {
                    //int n = read
                    fds[nfds].events = POLLOUT;
                    continue;
                }
            }
            else
            {
                // write (fds[i].fd, .....)
                n = read( new_connection, buffer, 1024));
                buffer[n] = '\0';
                write(1, buffer, 1024);
                close( new_connection);
                close( fds[i].fd );
            }
        }
        // accept(socket.getSockfd(), (struct sockaddr *)&address,(socklen_t *)&address_len);
        // fcntl( socket.getSockfd(), F_SETFL, O_NONBLOCK);
        // //accept(socket.getSockfd(), &address, (socklen_t *)sizeof(address));
        // fds[i].fd = socket.getSockfd();
        // fds[i].events = POLLIN;
        // n = poll(fds, i + 1, -1);
        // if (n == -1)
        // {
        //     perror("poll");
        //     exit(1);
        // }
        // exit(1);
        // // if (fds[i].revents & POLLIN)
        // // {

        //     // request.getHeader(socket.getSockfd());
        //     // request.write(socket.getSockfd());
        // // }
        // close(fds[i].fd);
        // i++;
    }
}