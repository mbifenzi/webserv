#include "Socket.hpp"
#include "Response.hpp"
#include "Request.hpp"
#include <fcntl.h>
#include <poll.h>

int main()
{
    // socket()
    std::string header;
    Socket *sock;
    sock[0] = Socket(AF_INET, SOCK_STREAM, 0, 1415, INADDR_ANY);
        // Request req;
    sock[0].event_loop();
    return 0;
}