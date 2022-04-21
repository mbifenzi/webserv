#ifndef RESPONSE_HPP
#define RESPONSE_HPP
#include "Socket.hpp"
#include <string>
class Response
{
    private:
        Socket sock;
        int status;
        std::string body;
        std::string contentType;
        std::string contentLength;
        std::string connection;
        std::string server;
        std::string date;
        std::string cacheControl;
        std::string expires;
        std::string pragma;
        std::string location;
        std::string contentEncoding;
        std::string vary;
        std::string transferEncoding;
        std::string varyAcceptEncoding;
        std::string varyAcceptEncodingGzip;
        std::string varyAcceptEncodingDeflate;
        std::string varyAcceptEncodingBrotli;
        std::string varyAcceptEncodingBrotliDeflate;
        std::string varyAcceptEncodingBrotliGzip;
        std::string varyAcceptEncodingBrotliGzipDeflate;
        std::string varyAcceptEncodingBrotliGzipDeflateGzip;
    public:
        Response();
        ~Response();
        void setStatus(int status);
        void setBody(std::string body);
        void setContentType(std::string contentType);
        void setContentLength(std::string contentLength);
        void setConnection(std::string connection);
        void setServer(std::string server);
        void setDate(std::string date);
        void setCacheControl(std::string cacheControl);
        void setExpires(std::string expires);
        void setPragma(std::string pragma);
        void setLocation(std::string location);
        void setContentEncoding(std::string contentEncoding);
        void setVary(std::string vary);
        void setTransferEncoding(std::string transferEncoding);
        void setVaryAcceptEncoding(std::string varyAcceptEncoding);
        void setVaryAcceptEncodingGzip(std::string varyAcceptEncodingGzip);
        void setVaryAcceptEncodingDeflate(std::string varyAcceptEncodingDeflate);
        void setVaryAcceptEncodingBrotli(std::string varyAcceptEncodingBrotli);
        void setVaryAcceptEncodingBrotliDeflate(std::string varyAcceptEncodingBrotliDeflate);
        void setVaryAcceptEncodingBrotliGzip(std::string varyAcceptEncodingBrotliGzip);
        void setVaryAcceptEncodingBrotliGzipDeflate(std::string varyAcceptEncodingBrotliGzipDeflate);
        void setVaryAcceptEncodingBrotliDeflateGzip(std::string varyAcceptEncodingBrotliDeflateGzip);
        void setVaryAcceptEncodingBrotliDeflateGzipGzip(std::string varyAcceptEncodingBrotliDeflateGzipGzip);
        void setVaryAcceptEncodingBrotliGzipDeflateGzip(std::string varyAcceptEncodingBrotliGzipDeflateGzip);
        void setVaryAcceptEncodingBrotliGzipDeflateGzipGzip(std::string varyAcceptEncodingBrotliGzipDeflateGzipGzip);
        std::string getResponse();
};

#endif