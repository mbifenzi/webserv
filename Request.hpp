#ifndef REQUEST_HPP
#define REQUEST_HPP
#include <string>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <sys/socket.h>
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
    public:
        Request();
        ~Request();
        std::map<std::string, std::string> Header;
        void getHeader(std::string line);
        void parseHeader(std::map<std::string, std::string> header);
        std::string split (std::string str, char delimiter);
        class Bad_request:public std::exception
        {
            const char* what() const throw()
            {
                return "Request error";
            }
        };
};

#endif