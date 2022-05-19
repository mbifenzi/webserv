#include "Poll.hpp"

Poll::Poll(std::vector<Socket> socket, int servers)
{
    this->sock = socket;
    // int bindfd;
    num_servers  = servers;
    for (int i = 0; i < servers; i++)
    {
        sock[i].initFd();
        // bindfd = bind(sock[i].getSockfd(), (struct sockaddr *) &sock[i].getAddr(), sizeof(sock[i].getAddr()));
        // if (bindfd < 0)
        // {
        //     std::cout << "bind error" << std::endl;
        // }
        // fcntl(sock[i].getSockfd(), F_SETFL, O_NONBLOCK);
        // listen(sock[i].getSockfd(), 10);
    }
}
Poll::~Poll()
{
    // delete request;
    // delete response;
}

void Poll::event_loop()
{
    struct sockaddr_in address;
    int address_len = sizeof(address);
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    std::vector<int> nfds;
    nfds =  std::vector<int>(num_servers);
    int n = 0;
    int connectFd = -1;
    std::cout << "debug" << std::endl;
    std::vector<int> vec;
    // for (int i = 0; i < sock.size();i++)
    //     vec.push_back(sock)
    struct pollfd *fd = sock[0].fds.data();
    std::cout << "NIl=>" << fd[0].fd << std::endl;
   int  dd = socket(AF_INET, SOCK_STREAM, 0);
    std::cout << dd << "ddddd" <<std::endl;
    while (1)
    {
            // printf("jldjhfl %d %d\n", sock[0].fds[0].fd, );÷
        for (int j = 0; j < num_servers; j++)
        {
            std::cout << sock[j].fds[0].fd << std::endl;
            nfds[j] = poll(sock[j].fds.data(), 1, -1);
            if (sock[j].fds[0].revents == 32)
            {
                std::cout << "error" << std::endl;
                exit(0);
            }
            std::cout << "-------" <<sock[j].fds[0].revents << std::endl; 
            if (nfds[j] < 0)
            {
                throw "poll() failed";
            }
            for (int i = 0; i < nfds[j]; i++)
            {
                if (sock[j].fds[i].fd == sock[j].getSockfd())
                {
                    connectFd = accept(sock[j].getSockfd(), (struct sockaddr *)&address, (socklen_t *)&address_len);
                    if (connectFd < 0)
                        throw "cannot accept\n";
                    fcntl(connectFd, F_SETFL, O_NONBLOCK);
                    sock[j].fds[nfds[j]].fd = connectFd;
                    sock[j].fds[nfds[j]].events = POLLIN;
                    nfds[j] = nfds[j] + 1;
                    std::cout << "accepted\n";
                }
                else if (sock[j].fds[i].fd == connectFd)
                {
                    char buf[4096];
                    n = read(connectFd, buf, 1024);
                    if (n < 0)
                    {
                        throw "cannot read\n";
                    }
                    if (n == 0)
                    {
                        std::cout << "client disconnected\n";
                        // sock[j].fds.erase(sock[j].fds.begin() + i);
                        // close(connectFd);
                        connectFd = -1; 
                        break;
                    }
                }
            }
        }
    }
}