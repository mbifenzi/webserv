#include "Request.hpp"

Request::Request()
{
    method = "";
    path = "";
    version = "";
    body = "";
    host = "";
    port = "";
    endHeader = false;
}

Request::~Request()
{
}

void Request::getHeader(std::string request)
{
    std::stringstream ss(request);
    std::string line;
    std::vector<std::string> lines;
    std::getline(ss, method, ' ');
    std::getline(ss, path, ' ');
    std::getline(ss, version, '\n');
    size_t pos ;
    while (std::getline(ss, line, '\n'))
    {
        lines.push_back(line);
    }
    for (size_t i = 0; i < lines.size(); i++)
    {
        if (lines[i].find("Host:") != std::string::npos)
        {
            pos = lines[i].find(":");
            host = lines[i].substr(pos + 1);
            std::cout << host << std::endl;
        }
        else if (size_t pos = lines[i].find("Port:") != std::string::npos)
        {
            pos = lines[i].find(":");
            port = lines[i].substr(pos + 1);
        }
        else if (size_t pos = lines[i].find("Content-Length:") != std::string::npos)
        {
            pos = lines[i].find(":");
            length = lines[i].substr(pos + 1);
        }
        else if (size_t pos = lines[i].find("\r\n") != std::string::npos)
        {
            endHeader = true;
        }
        else 
            throw Bad_request();
        if (endHeader == true)
        {
            body = lines[i];
        }
        else
        {

            pos = lines[i].find(":");
            std::string key = lines[i].substr(0, pos);
            std::string value = lines[i].substr(pos + 1);
            Header[key] = value;
        }
    }
}

std::string Request::split(std::string str, char delimiter)
{
    if (str.find(delimiter) != std::string::npos)
    {
        size_t pos = str.find(delimiter);
        return str.substr(pos + 1);
    }
    else
        throw Bad_request();
}