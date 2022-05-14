#include "Socket.hpp"
// #include "Response.hpp"
// #include "Request.hpp"
#include <fcntl.h>
#include "Poll.hpp"
#include <poll.h>

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    std::string header;
    Socket *sock[100];
    int servers = 2;
    sock[0] =  new Socket(AF_INET, SOCK_STREAM, 0, 1415, INADDR_ANY);
    sock[1] =  new Socket(AF_INET, SOCK_STREAM, 0, 1416, INADDR_ANY);
    Poll poll(sock, servers);
    poll.event_loop();
    return 0;
}