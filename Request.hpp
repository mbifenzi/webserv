#ifndef REQUEST_HPP
#define REQUEST_HPP
#include <string>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
// #include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <vector>
#include <map>
#include <sstream>

class Request
{
    private:
        
        std::string method;
        std::string path;
        std::string version;
        std::string host;
        std::string port;
        std::string body;
        std::string length;
        bool	endHeader;
        bool    endBody;
    public:
        Request();
        ~Request();
        std::map<std::string, std::string> Header;
        void getHeader(char *buffer);
        void getBody(std::vector<std::string>line, int i);
        void parseHeader(std::map<std::string, std::string> header);
        size_t split (std::string str, char delimiter);
        size_t split(std::string str, std::string delimiter);
        class Bad_request:public std::exception
        {
            const char* what() const throw()
            {
                return "Request error";
            }
        };
};

#endif