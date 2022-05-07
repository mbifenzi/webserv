#include "Socket.hpp"
#include "Response.hpp"
#include "Request.hpp"
#include <fcntl.h>
#include <poll.h>

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
    nfds = 1;
    while (1)
    {
        // std::cout << "Connection established" << std::endl;
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
                // while ((n = read(fds[i].fd,&buffer[n], 1)) > 0)
                // {
                //     n++;
                // }
                
                    n = read( new_connection, buffer, 1024);
                    buffer[n] = '\0';          
                    // request.getHeader(buffer);   
                    // write(fds[i].fd, "hello from server\n" , 18);
                    write(1, buffer , strlen(buffer));
                    close(new_connection);
                // close( fds[i].fd );
            }
        }
    }
}