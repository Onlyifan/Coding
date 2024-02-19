// 使用epoll实现一个基于TCP即时聊天，服务端需要支持断线重连。
#include <myselfc.h>

int main(int argc, char *argv[]){
    // ./exec 0.0.0.0 1234 
    ARGS_CHECK(argc, 3);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    int reuse = 1;
    int ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
            &reuse, sizeof(reuse));
    ERROR_CHECK(ret, -1, "setsockopt");

    ret = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    ERROR_CHECK(ret, -1, "bind");

    listen(sockfd, 50);

    int netfd = -1;

    int epfd = epoll_create(1);
    struct epoll_event events;
    events.events = EPOLLIN;
    events.data.fd = sockfd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &events);
    char buf[4096] = {0};

    printf("Server boot over.\n");
    struct epoll_event ready_set[1024];
    while(1){
        int ready_num = epoll_wait(epfd, ready_set, ARR_LEN(ready_set), -1);

        for(int i = 0; i < ready_num; ++i){
            if(ready_set[i].data.fd == sockfd){
                netfd = accept(sockfd, NULL, NULL);
                printf("client connecting success, netfd = %d\n", netfd);
                epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, NULL);
                events.events = EPOLLIN;
                events.data.fd = STDIN_FILENO;
                epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &events);
                events.events = STDIN_FILENO;
                events.data.fd = netfd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, netfd, &events);
            }
            else if(netfd != -1 && ready_set[i].data.fd == netfd){
                memset(buf, 0, sizeof(buf));
                ssize_t recv_len = recv(netfd, buf, sizeof(buf), 0);
                ERROR_CHECK(recv_len, -1, "recv");

                if(recv_len == 0){
                    printf("client lose connected.\n");
                    events.events = EPOLLIN;
                    events.data.fd = sockfd;
                    epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &events);
                    epoll_ctl(epfd, EPOLL_CTL_DEL, STDIN_FILENO, NULL);
                    epoll_ctl(epfd, EPOLL_CTL_DEL, netfd, NULL);

                    close(netfd);
                    netfd = -1;
                    break;
                }

                printf("buf = %s\n", buf);
            }
            else if(netfd != -1 && ready_set[i].data.fd == STDIN_FILENO){
                memset(buf, 0, sizeof(buf));
                ssize_t read_len = read(STDIN_FILENO, buf, sizeof(buf));
                ERROR_CHECK(read_len, -1, "read");

                if(read_len == 0){
                    printf("Kick client.\n");
                    events.events = EPOLLIN;
                    events.data.fd = sockfd;
                    epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &events);
                    epoll_ctl(epfd, EPOLL_CTL_DEL, STDIN_FILENO, NULL);
                    epoll_ctl(epfd, EPOLL_CTL_DEL, netfd, NULL);

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
