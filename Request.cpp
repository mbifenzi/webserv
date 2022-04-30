#include "Request.hpp"
#include <fstream>
#include <string.h>
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
    std::vector<std::string>::iterator it;
    it = line.begin();
    if (Header.count("Transfer-Encoding") && Header.find("Transfer-Encoding")->second == "chunked")
    {
        if (it != line.end())
        {
            return;
        }
        if (*it == "0")
        {
            endBody = true;
            return;
        }
        else
        {
            size_t bifenzi;
            std::stringstream ss;
            ss << std::hex << (*it);
            int size = 0;
            ss >> size;
            int sized = (*it).size();
            int j = 0;
            ++it;
            while (true)
            {
                j++;
                if (j == sized)
                {
                    break;
                }
                if (size == 0)
                {
                    break;
                }
                //std::cerr << "size is :" << line[i].size() << std::endl;
                // if (line[i].size() == 0)
                // {
                    // endBody = true;
                    // return;
                // }
                if (it != line.end() && *it == "\r\0")
                {
                   return;
                }
                bifenzi = (*it).size();
                if ((*it)[bifenzi - 1] == '\r')
                {
                    body += (*it).substr(0, bifenzi - 1) + "\n";
                    it++;
                }
                else
                {
                    body += (*it) + "\n";
                    it++;
                }
            }
        }
    }
    else
    {
        for (size_t j = i; j < (*it).size(); j++)
        {
            body += (*it)[j];
        }
        endBody = true;
    }
   
}

void Request::getHeader(std::string request)
{
    endBody = false;
    std::stringstream ss(request);
    std::string line;
    endHeader = false;
    std::vector<std::string> lines;
    std::getline(ss, method, ' ');
    std::getline(ss, path, ' ');
    std::getline(ss, version, '\n');
    size_t pos;
    
    while (std::getline(ss, line, '\n'))
        lines.push_back(line);

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
            std::string value = lines[i].substr(pos + 2, split(lines[i], '\r') - pos - 2);
            Header[key] = value;
        }
        if (endHeader == true)
        {
            getBody(lines, i);
            break ;
        }
    }
    // std::ofstream outfile;
    // outfile.open("/Users/mbifenzi/Desktop/1337/webserv/file.txt");
    // outfile << body;
    // outfile.close();
}

size_t Request::split(std::string str, char delimiter)
{
    if (str.find(delimiter) != std::string::npos)
    {
        size_t pos = str.find(delimiter);
        return pos;
    }
    else
    {
        std::cout << "No delimiter" << std::endl;
        // throw Bad_request();
    }
    return 0;
}

size_t Request::split(std::string str, std::string delimiter)
{
    if (str.find(delimiter) != std::string::npos)
    {
        size_t pos = str.find(delimiter);
        return pos;
    }
    else
    {
        std::cout << "No delimiter" << std::endl;
        // throw Bad_request();
    }
    return 0;
}