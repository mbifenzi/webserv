#include "Socket.hpp"

void Socket::event_loop()
{
    struct sockaddr_in address;
    int address_len = sizeof(address);
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    // int new_connection;
    int nfds;
    int n = 0;
    // int index = 0;
    fds[0].fd = sockfd;
    fds[0].events = POLLIN;
    nfds = 1;

    while (1)
    {
        nfds = poll(&fds[0], nfds, -1);
        if (nfds < 0)
        {
            throw "poll() failed";
        }
        for (size_t i = 0; i < fds.size(); i++)
        {
            if (fds[i].revents & POLLIN)
            {
                if (fds[i].fd == sockfd)
                {
                    connectfd = accept(sockfd, (struct sockaddr *)&address, (socklen_t *)&address_len);
                    if (connectfd < 0)
                    {
                        throw "cannot accept\n";
                    }
                    fcntl(connectfd, F_SETFL, O_NONBLOCK);
                    fds[nfds].fd = connectfd;
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