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
    Socket socket[100];
    int servers = 2;
    socket[0] =  new Socket(AF_INET, SOCK_STREAM, 0, 1415, INADDR_ANY);
    socket[1] =  new Socket(AF_INET, SOCK_STREAM, 0, 1416, INADDR_ANY);
    Poll Poll(socket, servers);
    Poll.event_loop();
    return 0;
}