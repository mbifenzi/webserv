#include "Poll.hpp"

Poll::Poll(Socket *sock, int server_count)
{
    this->sock = sock;
    this->request = new Request();
    this->response = new Response();
    // this->connectfd = -1;
    num_servers  = server_count;
    // fds = std::vector<fd_t>(1);
    for (int i = 0; i < server_count; i++)
    {
        sock[i].initFd();
        connectfd[i] = -1;
    }
}

void Poll::event_loop()
{
    struct sockaddr_in address;
    int address_len = sizeof(address);
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    // int new_connection;
    std::vector<int> nfds;
    // fds.push_back(fd_t());
    // fds[0].fd = 0;
    int n = 0;
    // int index = 0;
    // std::cout << sockfd << std::endl;
    // std::cout << fds[0].fd << std::endl;
    // fds[0].fd = sock->getSockfd();
    
    // nfds[] = {1};
    std::cout << "debug" << std::endl;
    while (1)
    {
        for (int j = 0; j < num_servers; j++)
        {
            nfds[j] = poll(&sock[j].fds[0], nfds[j], -1);
            if (nfds[j] < 0)
        {
            
            throw "poll() failed";
        }
        }
        
        // nfds = poll(&fds[0], nfds, -1);
        
        for (size_t i = 0; i < sock[i].fds.size(); i++)
        {
            if (sock[i].fds[i].revents & POLLIN)
            {
                for (int k = 0; k < num_servers; k++)
                {
                    if (sock[k].fds[i].fd == sock[k].getSockfd())
                    {
                        connectfd[k] = accept(sock[k].getSockfd(), (struct sockaddr *)&address, (socklen_t *)&address_len);
                        if (connectfd[k] < 0)
                        {
                            throw "cannot accept\n";
                        }
                        fcntl(connectfd[k], F_SETFL, O_NONBLOCK);
                        sock[k].fds[nfds[i]].fd = connectfd[i];
                        sock[k].fds[nfds[i]].events = POLLIN;
                        nfds++;
                        std::cout << "accepted\n";
                    }
                }
                {
                    /* code */
                }
                
                if (fds[i].fd == sock->getSockfd())
                {
                    connectfd = accept(sockfd, (struct sockaddr *)&address, (socklen_t *)&address_len);
                    if (connectfd < 0)
                    {
                        throw "cannot accept\n";
                    }
                    fcntl(connectfd, F_SETFL, O_NONBLOCK);
                    fds[nfds].fd =  connectfd;
                    fds[nfds].events = POLLIN;
                    nfds++;
                    std::cout << "accepted\n";
                }
                    
            }
            else if (fds[i].fd == connectfd)
            {
                char buf[4096];
                n = read(connectfd, buf, 1024);
                if (n < 0)
                {
                    throw "cannot read\n";
                }
                if (n == 0)
                {
                    std::cout << "client disconnected\n";
                    fds.erase(fds.begin() + i);
                    close(connectfd);
                    connectfd = -1; 
                    break;
                }
                std::cout << "received: " << buf << std::endl;
                // std::stringstream ss;
                // ss << buf;
                // Request req(ss);
                // Response res;
                // res.set_status_code(200);
                // res.set_status_message("OK");
                // res.set_content_type("text/html");
                // res.set_content("<h1>Hello World</h1>");
                // std::stringstream ss2;
                // res.print(ss2);
                // std::string s = ss2.str();
                // std::cout << s << std::endl;
                // write(connectfd, s.c_str(), s.size());
                // fds.erase(fds.begin() + i);
                close(connectfd);
                connectfd = -1;
                break;
            }
        }
    }
}