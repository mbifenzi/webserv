#include "Request.hpp"
#include <fstream>

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
    (void)i;
    (void) line;
    std::cout << "|" <<  Header["Transfer-Encoding"] << "$" << std::endl;
    // std::cout << "-" << std::endl;
    // if (Header.count("Transfer-Encoding") && Header.find("Transfer-Encoding")->second == "chunked")
    // {
    //     if (line[i] == "0")
    //     {
    //         endBody = true;
    //         return;
    //     }
    //     else
    //     {
    //         std::stringstream ss;
    //         ss << std::hex << line[i];
    //         int size = 0;
    //         ss >> size;
    //         std::cout << "siiiize " << size << std::endl;
    //         std::string chunk = "";
    //         for (int j = i + 1; j < i + size + 1; j++)
    //         {
    //             chunk += line[j];
    //         }
    //         body += chunk;
    //         getBody(line, i + size + 1);
    //     }
    // }
    // else
    // {
    //     for (size_t j = i; j < line.size(); j++)
    //     {
    //         body += line[j];
    //         std::cout <<  " HADA BODY " << body << std::endl;
    //     }
    //     endBody = true;
    // }
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

            std::map<std::string, std::string> headersss = Header;
            for (std::map<std::string, std::string>::iterator it = headersss.begin(); it != headersss.end(); ++it)
                std::cout << it->first << "=>" << it->second << std::endl;
            i += 2;
        }
        else if (endHeader == false)
        {
            pos = split(lines[i], ':');
            std::string key = lines[i].substr(0, pos);
            std::string value = lines[i].substr(pos + 2, split(lines[i], "\r\n"));
            Header[key] = value;
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