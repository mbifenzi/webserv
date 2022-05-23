#ifndef POLL_HPP
#define POLL_HPP
#include "Socket.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include <fcntl.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fstream>

class Poll {
    private:
        std::vector<Socket> sock;
        // struct pollfd pfds[100];
        typedef struct pollfd pfd_t;
        std::vector<pfd_t> pfds;
        // Request *request;
        // Response *response;
        // std::vector<int> nfds;
        int num_servers;
    public:
        Poll(std::vector<Socket> socket, int servers);
        ~Poll();
        void add(int fd, int events);
        void remove(int fd);
        void clear();
        int wait(int timeout);
        int get_fd(int index);
        // void getEvents(std::vector<pfd_t> pfds ,int server, int client, int nfds,);
        int get_revents(int index);
        int get_count();
        int get_connectfd();
        void set_connectfd(int connectfd);
        // void event_loop();
        void test_loop();
        class Suck_it:public std::exception
        {
            const char* what() const throw()
            {
                return "poll() failed";
            }
        };
};

#endif