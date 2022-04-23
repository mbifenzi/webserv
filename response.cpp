#include "Response.hpp"

Response::Response(Socket socket)
{
    // *sock = &socket;
    status = 200;
    body = "";
    contentType = "text/html";
    contentLength = "";
    connection = "";
    server = "";
    date = "";
    cacheControl = "";
    expires = "";
    pragma = "";
    location = "";
    contentEncoding = "";
    vary = "";
    transferEncoding = "";
    varyAcceptEncoding = "";
    varyAcceptEncodingGzip = "";
    varyAcceptEncodingDeflate = "";
    varyAcceptEncodingBrotli = "";
    varyAcceptEncodingBrotliDeflate = "";
    varyAcceptEncodingBrotliGzip = "";
}

void Response::setBody(std::string body)
{
    this->body = body;
}

void Response::setContentType(std::string contentType)
{
    this->contentType = contentType;
}
// write a function that take the path and execute the cgi script
// and return the response
std::string Response::getResponse()
{
    std::string response = "";
    response += "HTTP/1.1 " + std::to_string(status) + " OK\r\n";
    response += "Content-Type: " + contentType + "\r\n";
    response += "Content-Length: " + contentLength + "\r\n";
    response += "Connection: " + connection + "\r\n";
    response += "Server: " + server + "\r\n";
    response += "Date: " + date + "\r\n";
    response += "Cache-Control: " + cacheControl + "\r\n";
    response += "Expires: " + expires + "\r\n";
    response += "Pragma: " + pragma + "\r\n";
    response += "Location: " + location + "\r\n";
    response += "Content-Encoding: " + contentEncoding + "\r\n";
    response += "Vary: " + vary + "\r\n";
    response += "Transfer-Encoding: " + transferEncoding + "\r\n";
    response += "Vary: " + varyAcceptEncoding + "\r\n";
    response += "Vary: " + varyAcceptEncodingGzip + "\r\n";
    response += "Vary: " + varyAcceptEncodingDeflate + "\r\n";
    response += "Vary: " + varyAcceptEncodingBrotli + "\r\n";
    response += "Vary: " + varyAcceptEncodingBrotliDeflate + "\r\n";
    response += "Vary: " + varyAcceptEncodingBrotliGzip + "\r\n";
    response += "Vary: " + varyAcceptEncodingBrotliGzipDeflate + "\r\n";
    response += "Vary: " + varyAcceptEncodingBrotliDeflateGzip + "\r\n";
    response += "Vary: " + varyAcceptEncodingDeflateGzip + "\r\n";
    response += "\r\n";
    response += body;
    return response;
}