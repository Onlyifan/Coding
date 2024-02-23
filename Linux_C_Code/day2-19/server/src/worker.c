#include "process_pool.h"

int worker_create(int worker_nums, worker_data_t *worker_data_arr) {
    for (int i = 0; i < worker_nums; ++i) {
        int sockpipefd_pair[2];
        socketpair(AF_LOCAL, SOCK_STREAM, 0, sockpipefd_pair);
        pid_t pid = fork();

        // worker_process
        if (pid == 0) {
            close(sockpipefd_pair[1]);
            worker_loop(sockpipefd_pair[0]);
        }

        // main_process
        close(sockpipefd_pair[0]);
        worker_data_arr[i].pid = pid;
        worker_data_arr[i].status = FREE;
        worker_data_arr[i].id= i;
        worker_data_arr[i].sockpipefd = sockpipefd_pair[1];
        printf("create a worker, "
                "worker_id = %d, "
                "sockpipefd = %d\n",
                worker_data_arr[i].id, worker_data_arr[i].sockpipefd);
    }
    return 0;
}

int worker_loop(int sockpipefd) {
    for (;;) {
        printf("A worker process is waiting task.\n");
        bool exit_flag;
        int netfd;
        int ret = recvfd(sockpipefd, &netfd, &exit_flag);
        ERROR_CHECK(ret, -1, "worker_loop recv");

        if (exit_flag == true) {
            printf("a worker is going to die.\n");
            exit(0);
        }

        printf("receive a task.\n");

        ret = trans_file(netfd);
        ERROR_CHECK(ret, -1, "worker_loop trans_file");

        close(netfd);
        printf("finishde a task\n");
        int flag = 0;
        send(sockpipefd, &flag, sizeof(flag), 0);
    }
}
