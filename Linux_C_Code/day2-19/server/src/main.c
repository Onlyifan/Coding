#include "process_pool.h"

#define EPOLL_READY_SET_SIZE 1024
#define EVENT_DATA_OF_EXIT 0x80000000
#define EVENT_DATA_OF_SOCK 0x40000000

int exit_pipefd[2];

static void handler(int signum){
    ssize_t ret = write(exit_pipefd[1], "0", 1);
}

int main(int argc, char *argv[]){
    // ./main server_ip port worker_nums
    ARGS_CHECK(argc, 4);

    int worker_nums = atoi(argv[3]);
    worker_data_t *worker_data_arr = (worker_data_t *)calloc(worker_nums, sizeof(worker_data_t));
    worker_create(worker_nums, worker_data_arr);

    int sockfd = tcp_init(argv[1], argv[2]);
    ERROR_CHECK(sockfd, -1, "main sockfd");

    int epfd = epoll_create(1);
    epoll_add(epfd, sockfd, EVENT_DATA_OF_SOCK);
    for (uint32_t i = 0; i < worker_nums; ++i) {
        epoll_add(epfd, worker_data_arr[i].sockpipefd, i);
    }

    pipe(exit_pipefd);
    signal(SIGUSR1, handler);
    epoll_add(epfd, exit_pipefd[0], EVENT_DATA_OF_EXIT);

    while(1){
        struct epoll_event ready_set[EPOLL_READY_SET_SIZE];
        int ready_nums = epoll_wait(epfd, ready_set, ARR_LEN(ready_set), -1);
        for (int i = 0; i < ready_nums; ++i) {
            // 关闭服务
            if(ready_set[i].data.u32 == EVENT_DATA_OF_EXIT) {
                for (size_t i = 0; i < worker_nums; ++i) {
                    sendfd(worker_data_arr[i].sockpipefd, 0, true);
                    printf("send exit_flag to a worker, id = %d, pid = %d\n",
                            worker_data_arr[i].id, worker_data_arr[i].pid);
                }

                for (int i = 0; i < worker_nums; ++i) {
                    wait(NULL);
                }

                printf("kill all worker.\n");
                break;
            }

            // 监听到新客户端连接
            if (ready_set[i].data.u32 == EVENT_DATA_OF_SOCK) {
                int netfd = accept(sockfd, NULL, NULL);
                printf("accept a connect\n");

                for (int i = 0; i < worker_nums; ++i) {
                    if (worker_data_arr[i].status == FREE) {
                        sendfd(worker_data_arr[i].sockpipefd, netfd, false);
                        worker_data_arr[i].status = BUSY;
                        break;
                    }
                }

                close(netfd);
                continue;
            }

            //某个worker完成任务
            uint32_t worker_id = ready_set[i].data.u32;
            int flag;
            recv(worker_data_arr[worker_id].sockpipefd, &flag, sizeof(flag), 0);
            if(flag == 0) {
                printf("recv sign = %d from worker.\n", flag);
            }


            worker_data_arr[worker_id].status = FREE;

        }
    }

    return 0;
}
