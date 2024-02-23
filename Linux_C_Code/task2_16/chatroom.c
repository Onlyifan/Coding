#include <myselfc.h>

#define LISTEN_CONNECT_MAX 50
#define BUF_SIZE 4096
#define READY_SET_SIZE 1024
#define TIME_OUT_LIMIT 10
#define CHAT_CONNECTION_MAX 500
#define SOCKFD_SYMBOL 0x80000000

typedef struct chat_status_s {
    bool is_alive;
    int netfd;
    time_t last_active;
}chat_status_t;

int main(int argc, char *argv[]){
    // ./exec 0.0.0.0 23333 
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

    listen(sockfd, LISTEN_CONNECT_MAX);

    int epfd = epoll_create(1);
    struct epoll_event events;
    events.events = EPOLLIN;
    events.data.u32 = SOCKFD_SYMBOL;
    epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &events);

    struct epoll_event ready_set[READY_SET_SIZE];

    char buf[BUF_SIZE] = {0};

    uint32_t current_chat_id = 0;
    chat_status_t chat_status_arr[CHAT_CONNECTION_MAX];
    for (int i = 0; i < CHAT_CONNECTION_MAX; ++i) {
        chat_status_arr[i].is_alive = false;
    }

    time_t now;
    printf("Server success init.\n");
    for(;;) {
        time_t now = time(NULL);
        int ready_num = epoll_wait(epfd, ready_set, ARR_LEN(ready_set), 1000);

        for(int i = 0; i < ready_num; ++i){
            if(ready_set[i].data.u32 == SOCKFD_SYMBOL){
                int netfd = accept(sockfd, NULL, NULL);
                ERROR_CHECK(netfd, -1, "accept");
                printf("New client connecting success, netfd = %d\n", netfd);

                chat_status_arr[current_chat_id].netfd = netfd;
                chat_status_arr[current_chat_id].is_alive = true;
                chat_status_arr[current_chat_id].last_active = time(NULL);

                events.events = EPOLLIN;
                events.data.u32 = current_chat_id;
                epoll_ctl(epfd, EPOLL_CTL_ADD, netfd, &events);

                ++current_chat_id;
                continue;
            }

            // 到这里说明是netfd就绪
            uint32_t chat_id = ready_set[i].data.u32;
            int netfd = chat_status_arr[chat_id].netfd;

            memset(buf, 0, sizeof(buf));
            ssize_t recv_len = recv(netfd, buf, sizeof(buf), 0);
            ERROR_CHECK(recv_len, -1, "recv");

            if(recv_len == 0){
                printf("1 client close connection.\n");
                epoll_ctl(epfd, EPOLL_CTL_DEL, netfd, NULL);
                chat_status_arr[chat_id].is_alive = false;
                close(netfd);
                continue;
            }
            chat_status_arr[chat_id].last_active = time(NULL);
            for(int i = 0; i < current_chat_id; ++i){
                if(chat_status_arr[i].is_alive == true && i != chat_id){
                    send(chat_status_arr[i].netfd, buf, strlen(buf), 0);
                }
            }
        }

        for(int i = 0; i < current_chat_id; ++i){
            if(chat_status_arr[i].is_alive == true && now - chat_status_arr[i].last_active > TIME_OUT_LIMIT){
                epoll_ctl(epfd, EPOLL_CTL_DEL, chat_status_arr[i].netfd, NULL);
                chat_status_arr[i].is_alive = 0;
                close(chat_status_arr[i].netfd);
            }
        }
    }

    return 0;
}
