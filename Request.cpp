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

void Request::getBody(std::vector<std::string>line, int i)
{
    for (size_t j = i; j < line.size(); j++)
    {
        body += line[j];
    }
}

void Request::getHeader(std::string request)
{
    std::stringstream ss(request);
    std::string line;
    endHeader = false;
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
            std::cout << "host" << std::endl;
            pos = lines[i].find(":");
            host = lines[i].substr(0, pos);
            port = lines[i].substr(pos + 2);
        }
        if (lines[i].find("Content-Length:") != std::string::npos)
        {
            pos = lines[i].find(":");
            length = lines[i].substr(pos + 2);
        }
        else if (lines[i] == "\r")
        {
            std::cout << "backslash" << std::endl;
            endHeader = true;
        }
        else if (endHeader == false)
        {
            std::cout << "------------" << std::endl;
            std::cout << lines[i] << std::endl;
            pos = split(lines[i], ':');
            std::string key = lines[i].substr(0, pos);
            std::string value = lines[i].substr(pos + 1);
            Header[key] = value;
        }
        if (endHeader == true)
        {
            std::cout << "true" << std::endl;
            getBody(lines, i);
            break ;
        }
    }
}

size_t Request::split(std::string str, char delimiter)
{
    if (str.find(delimiter) != std::string::npos)
    {
        size_t pos = str.find(delimiter);
        return pos;
    }
    else
        throw Bad_request();
}