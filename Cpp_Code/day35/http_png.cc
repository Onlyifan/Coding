#include <iostream>
#include <myselfc.h>
#include <string>


using namespace std;


class HttpServer {
private:
    int _fd;
    string _ip;
    unsigned short _port;

public:
    HttpServer(const string &ip, unsigned short port)
        : _fd(-1)
        , _ip(ip)
        , _port(port) {}

    ~HttpServer( ) {
        if (_fd > 0) { close(_fd); }
    }

    void start( ) {
        _fd = socket(AF_INET, SOCK_STREAM, 0);
        if (_fd < 0) {
            perror("socket");
            return;
        }
        int reuseAddr = 1;
        int ret = setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &reuseAddr, sizeof(reuseAddr));
        if (ret < 0) {
            perror("setsockopt");
            return;
        }
        struct sockaddr_in serveraddr;
        memset(&serveraddr, 0, sizeof(serveraddr));
        serveraddr.sin_family = AF_INET;
        serveraddr.sin_addr.s_addr = inet_addr(_ip.c_str( ));
        serveraddr.sin_port = htons(_port);
        ret = bind(_fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
        if (ret < 0) {
            perror("bind");
            return;
        }
        ret = listen(_fd, 10);
        if (ret < 0) {
            perror("listen");
            return;
        }
    }
    void recvAndShow( ) {
        while (true) {
            int netfd = accept(_fd, nullptr, nullptr);
            char buff[1024] = { 0 };
            int ret = recv(netfd, buff, sizeof(buff), 0);

            printf("ret: %d\nrecv: %s\n", ret, buff);


            string msg = response( );
            printf("\r\n%s\n", msg.c_str( ));
            ret = send(netfd, msg.c_str( ), msg.size( ), 0);
            close(netfd);
        }
    }

    string response( ) {
        string startLine = "HTTP/1.1 200 OK\r\n";
        string headers = "Server: MyHttpServer\r\n";
        int fpp = open("/Users/Onlyifan/Tsukyi/Coding/Cpp_Code/day35/test.png", O_RDWR);
        if (fpp < 0) { exit(EXIT_FAILURE); }
        char picturebuf[4096000] = { 0 };

        int pictureSize = read(fpp, picturebuf, sizeof(picturebuf));
        // string body(picturebuf, picturebuf + pictureSize);
        string body(picturebuf, pictureSize);
        close(fpp);

        headers += "Content-Type: image/png\r\n";
        headers += "Content-Legnth: " + std::to_string(body.size( )) + "\r\n";
        string emptyLine("\r\n");
        return startLine + headers + emptyLine + body;
    }
};

void test0( ) {
    HttpServer httpserver("0.0.0.0", 1280);
    httpserver.start( );
    httpserver.recvAndShow( );
}

int main( ) {
    test0( );
    return 0;
}
