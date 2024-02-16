// 使用epoll实现一个基于TCP即时聊天，服务端需要支持断线重连。
#include <myselfc.h>

int main(int argc, char *argv[]){
    // ./exec 0.0.0.0 1234 
    ARGS_CHECK(argc, 3);
    int ret;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    ret = connect(sockfd,
            (struct sockaddr *)&server_addr, sizeof(server_addr));
    ERROR_CHECK(ret, -1, "connect");

    int epfd = epoll_create(1);
    struct epoll_event events;
    
    events.events = EPOLLET;
    events.data.fd = sockfd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &events);
    events.events = EPOLLET;
    events.data.fd = STDIN_FILENO;
    epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &events);
    char buf[4096] = {0};

    while(1){
        struct epoll_event ready_set[64];
        int ready_num = epoll_wait(epfd, ready_set, ARR_LEN(ready_set), -1);

        for(int i = 0; i < ready_num; ++i){
            if(ready_set[i].data.fd == sockfd){
                memset(buf, 0, sizeof(buf));
                ssize_t recv_len = recv(sockfd, buf, sizeof(buf), 0);
                ERROR_CHECK(recv_len, -1, "recv");

                if(recv_len == 0){
                    close(sockfd);
                    return 0;
                }

                printf("buf = %s\n", buf);
            }
            else if(ready_set[i].data.fd == STDIN_FILENO){
                memset(buf, 0, sizeof(buf));
                ssize_t read_len = read(STDIN_FILENO, buf, sizeof(buf));
                ERROR_CHECK(read_len, -1, "read");
                ret = send(sockfd, buf, read_len, 0);
                ERROR_CHECK(ret, -1, "recv");
            }
        }
    }

    return 0;
}
