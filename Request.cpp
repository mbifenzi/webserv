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
    if (Header.count("Transfer-Encoding") && Header["Transfer-Encoding"] == "chunked")
    {
        endHeader = false;
        if (line[i] == "0")
        {
            endHeader = true;
            return;
        }
        else
        {
            std::stringstream ss;
            ss << std::hex << line[i];
            int size = 0;
            ss >> size;
            std::string chunk = "";
            for (int j = i + 1; j < i + size + 1; j++)
            {
                chunk += line[j];
            }
            body += chunk;
            getBody(line, i + size + 1);
        }
    }
    else
    {
        for (size_t j = i; j < line.size(); j++)
        {
            body += line[j];
        }
        endHeader = true;
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
    size_t pos;
    while (std::getline(ss, line, '\n'))
    {
        lines.push_back(line);
    }
    for (size_t i = 0; i < lines.size(); i++)
    {
        if (lines[i] == "\r")
        {
            endHeader = true;
            i++;
        }
        else if (endHeader == false)
        {
            pos = split(lines[i], ':');
            std::string key = lines[i].substr(0, pos);
            std::string value = lines[i].substr(pos + 1);
            Header[key] = value;
            std::cout << key << ": " << value << std::endl;
    
        }
        if (endHeader == true)
        {
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