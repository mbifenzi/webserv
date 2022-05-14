#ifndef POLL_HPP
#define POLL_HPP
#include "socket.hpp"
#include "Request.hpp"
#include "Response.hpp"

class Poll {
private:
    Socket *sock;
    Request *request;
    Response *response;
    int connectfd;
public:
    Poll(Socket *sock);
    ~Poll();
    void add(int fd, int events);
    void remove(int fd);
    void clear();
    int wait(int timeout);
    int get_fd(int index);
    int get_events(int index);
    int get_revents(int index);
    int get_count();
    int get_connectfd();
    void set_connectfd(int connectfd);
    void set_fds(std::vector<fd_t> fds);
    std::vector<fd_t> get_fds();
    void event_loop();
    class Suck_it:public std::exception
    {
        const char* what() const throw()
        {
            return "poll() failed";
        }
    };
};
    // struct pollfd *fds;
    // int nfds;
};


#endif