#include "Poll.hpp"

Poll::Poll(std::vector<Socket> socket, int servers)
{
    this->sock = socket;
    // this->request = new Request();
    // this->response = new Response();
    int bindfd;
    num_servers  = servers;
    for (int i = 0; i < servers; i++)
    {
        sock[i].initFd();
        bindfd = bind(sock[i].getSockfd(), (struct sockaddr *) &sock[i].getAddr(), sizeof(sock[i].getAddr()));
        if (bindfd < 0)
        {
            // throw "cannot bind\n";
            std::cout << "bind error" << std::endl;
        }
        fcntl(sock[i].getSockfd(), F_SETFL, O_NONBLOCK);
        listen(sock[i].getSockfd(), 10);
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
    // std::cout << "sock = " << sock[0].() << std::endl;
    while (1)
    {
        for (int j = 0; j < num_servers; j++)
        {

            nfds[j] = poll(&sock[j].fds[0], nfds[j], -1);
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
                        sock[j].fds.erase(sock[j].fds.begin() + i);
                        close(connectFd);
                        connectFd = -1; 
                        break;
                    }
                }
            }
        }
    }
}