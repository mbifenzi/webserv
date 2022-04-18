


#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int sockfd;
    struct sockaddr_in servaddr;


    servaddr.sin_family = AF_INET; // or AF_INET6
    servaddr.sin_port = htons(8080);
    
    // servaddr.sin_zero[0] = 0;
    
    servaddr.sin_addr.s_addr = INADDR_ANY;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    listen(sockfd, 10);

    
    while (1) {
        int connfd = accept(sockfd, (struct sockaddr *)NULL, NULL);
        char buffer[1024];
        int n = read(connfd, buffer, 1024);
        buffer[n] = '\0';
        std::cout << buffer << std::endl;

        //send data
        char msg[] = "Hello World";
        write(connfd, msg, strlen(msg));


        close(connfd);
    }

    return 0;
}
