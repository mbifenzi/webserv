#include "Poll.hpp"
#include <fcntl.h>
#include <string.h>
Poll::Poll(std::vector<Socket> socket, int servers)
{
    this->sock = socket;
    num_servers  = servers;
    pfds = std::vector<pfd_t>(servers);
    for (int i = 0; i < servers; i++)
    {
        pfds[i].fd = socket[i].getSockfd();
        pfds[i].events = POLLIN;
        pfds[i].revents = 0;
    }


}
Poll::~Poll()
{

}

void Poll::event_loop()
{
    struct sockaddr_in address;
    int address_len = sizeof(address);
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    int nfds = 1;
     char buf[4096];
     int valread;

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
        std::cout << "polling..." << std::endl;
        ret  = poll(pfds.data(), nfds, -1);
        fcntl(pfds[0].fd, F_SETFL, O_NONBLOCK);
        for (int j = 0; j < nfds; j++)
        {
            if (pfds[j].revents & POLLIN)
            {
                for (int i = 0; i < num_servers)
                {
                    if (pfds[j].fd == sock[i].getSockfd())
                {
                    connectFd = accept(sock[i].getSockfd(), (struct sockaddr *) &address, (socklen_t *) &address_len); // connection
                    if (connectFd < 0)
                    {
                        perror("accept");
                        exit(1);
                    }
                    // fcntl(connectFd, F_SETFL, O_NONBLOCK);
                    pfds[nfds].fd = connectFd;
                    pfds[nfds].events = POLLIN;
                    nfds++; // 2
                    continue;
                }
                    else
                    {
                        valread = read(pfds[j].fd, buf, 3000);
                            perror("read ");

                        if (valread < 0)
                        {
                            perror("read");
                            exit(1);
                        }
                        pfds[j].events = POLLOUT;
                        continue;
                    }
                }
            }
            else if (pfds[j].revents & POLLOUT) // there is some kinda request
            {
                std::cout << "writing j:" << j << std::endl;
                
                char *header = strdup("HTTP/1.1 200 OK\r\nContent-Type: text/html\nConnection: close\r\n\r\n");
                char *msg = strdup("<html><body><h1>Hello World</h1></body></html>");
                write(pfds[j].fd, header, strlen(header));
                write(pfds[j].fd, msg, strlen(msg));
                                                        perror("write ");

                // pfds[j].events = POLLIN;
                std::cout << "====>" << pfds[j].fd << std::endl;
                close(pfds[j].fd);
                perror("CLose ");
                pfds[j].fd = -1;
                pfds[j].events = 0;
                pfds[j].revents = 0;
                nfds--;
            }
        }
            
    }
}