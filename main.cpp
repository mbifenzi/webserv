#include "Socket.hpp"
// #include "Response.hpp"
// #include "Request.hpp"
#include <fcntl.h>
#include <poll.h>

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    std::string header;
    std::cout << "debug" << std::endl;
    Socket *sock[1];
    sock[0] =  new Socket(AF_INET, SOCK_STREAM, 0, 1415, INADDR_ANY);
    sock[0].event_loop();
    return 0;
}