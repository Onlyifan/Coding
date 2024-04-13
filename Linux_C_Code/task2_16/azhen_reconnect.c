#include <myselfc.h>


int main(int argc, char *argv[]) {
    // ./5_azhen 192.168.72.128 1234
    // 192.168.72.128:1234 是服务端的ip端口
    ARGS_CHECK(argc, 3);
    int                sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[2]));
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
    int reuse = 1; // 允许重用
    int ret = setsockopt(sockfd, SOL_SOCKET,
                         SO_REUSEADDR, &reuse, sizeof(reuse));
    ERROR_CHECK(ret, -1, "setsockopt");
    ret = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    ERROR_CHECK(ret, -1, "bind");
    listen(sockfd, 50);
    int netfd = -1; // 最开始没有阿强连入

    int                epfd = epoll_create(1);       // 创建epoll文件对象
    struct epoll_event events;                       // 什么情况就绪？ 就绪了怎么办？
    events.events = EPOLLIN;                         // 读就绪
    events.data.fd = sockfd;                         // 就绪之后放入sockfd
    epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &events); // 最开始只监听了sockfd
    char buf[4096] = {0};
    while (1) {
        struct epoll_event readySet[64];
        int                readyNum = epoll_wait(epfd, readySet, 64, -1);

        for (int i = 0; i < readyNum; ++i) {
            if (readySet[i].data.fd == sockfd) {
                netfd = accept(sockfd, NULL, NULL);
                printf("aqiang is connected!,netfd = %d\n", netfd);
                epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, NULL);
                events.events = EPOLLIN;
                events.data.fd = STDIN_FILENO;
                epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &events);
                events.events = EPOLLIN;
                events.data.fd = netfd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, netfd, &events);
            } else if (netfd != -1 && readySet[i].data.fd == netfd) {
                bzero(buf, sizeof(buf));
                ssize_t sret = recv(netfd, buf, sizeof(buf), 0);
                if (sret == 0) {
                    printf("aqiang has dead!\n");
                    events.events = EPOLLIN;
                    events.data.fd = sockfd;
                    epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &events);
                    epoll_ctl(epfd, EPOLL_CTL_DEL, netfd, NULL);
                    epoll_ctl(epfd, EPOLL_CTL_DEL, STDIN_FILENO, NULL);
                    close(netfd);
                    netfd = -1;
                    break;
                }
                printf("buf = %s\n", buf);
            } else if (netfd != -1 && readySet[i].data.fd == STDIN_FILENO) {
                bzero(buf, sizeof(buf));
                ssize_t sret = read(STDIN_FILENO, buf, sizeof(buf));
                if (sret == 0) {
                    printf("kick aqiang!\n");
                    events.events = EPOLLIN;
                    events.data.fd = sockfd;
                    epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &events);
                    epoll_ctl(epfd, EPOLL_CTL_DEL, netfd, NULL);
                    epoll_ctl(epfd, EPOLL_CTL_DEL, STDIN_FILENO, NULL);
                    close(netfd);
                    netfd = -1;
                    break;
                }
                send(netfd, buf, strlen(buf), 0);
            }
        }
    }
    return 0;
}
