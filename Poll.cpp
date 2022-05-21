#include "Poll.hpp"
#include <fcntl.h>
#include <string.h>
Poll::Poll(std::vector<Socket> socket, int servers)
{
    this->sock = socket;
    // int bindfd;
    num_servers  = servers;
    // for (int i = 0; i < servers; i++)
    // {
    //     sock[i].initFd();
    // }
    pfds[0].fd = socket[0].getSockfd();
    pfds[0].events = POLLIN;
    // pfds[1].fd = socket[1].getSockfd();
    // pfds[1].events = POLLIN;

}
Poll::~Poll()
{

}

void Poll::event_loop()
{
    struct sockaddr_in address;
    int address_len = sizeof(address);
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    //struct pollfd pfds[100];
    int nfds = 1;

    //std::vector<int> nfds;
   //nfds =  std::vector<int>(num_servers);
     char buf[4096];
     int valread;
   // nfds[0] = 1;
   // nfds[1] = 1;
    // int n = 0;
     int connectFd = -1;

    // get all servers fds
    // and gather them in one array 
    // and pass it poll()
    // when an event occurs to an FD, get the owner (server) of the fd
    // then...
    int ret;
    std::cout << "debug" << std::endl;
    while (1)
    {
        ret  = poll(pfds, nfds, -1);
        fcntl(pfds[0].fd, F_SETFL, O_NONBLOCK);
        std::cout << "nfds: " << nfds << std::endl;

        for (int j = 0; j <= nfds; j++)
        {
            if (pfds[j].revents & POLLIN)
            {
                if (pfds[j].fd == sock[0].getSockfd())
                {
                    connectFd = accept(sock[0].getSockfd(), (struct sockaddr *) &address, (socklen_t *) &address_len);
                    if (connectFd < 0)
                    {
                        perror("accept");
                        exit(1);
                    }
                    fcntl(connectFd, F_SETFL, O_NONBLOCK);
                    pfds[nfds].fd = connectFd;
                    pfds[nfds].events = POLLIN;
                    nfds++;
                     continue;
                }
                else
                {
                    valread = read(pfds[j].fd, buf, 3000);
                    if (valread < 0)
                    {
                        perror("read");
                        exit(1);
                    }
                    std::cout << "valread: " << valread << std::endl;
                    std::cout << "buf: " << buf << std::endl;
                    pfds[j].events = POLLOUT;
                    continue;
                }

            }
            else if (pfds[j].revents & POLLOUT)
            {
                std::cout << "writing j:" << j << std::endl;
                char *header = strdup("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
                char *msg = strdup("<html><body><h1>Hello World</h1></body></html>");
                write(pfds[j].fd, header, strlen(header));
                write(pfds[j].fd, msg, strlen(msg));
                close(pfds[j].fd);
                pfds[j].fd = -1;
                nfds--;

            }
        }
            
    }
}