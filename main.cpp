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
    std::vector<Socket> socketa;
    int servers = 2;
    socketa.push_back(Socket(AF_INET, SOCK_STREAM, 0, 1415, INADDR_ANY));
    socketa.push_back(Socket(AF_INET, SOCK_STREAM, 0, 1416, INADDR_ANY));
    Poll Poll(socketa, servers);
    Poll.event_loop();
    return 0;
}