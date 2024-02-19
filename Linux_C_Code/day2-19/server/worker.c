#include "process_pool.h"

int worker_create(int worker_nums, worker_data_t *worker_data_arr) {
    for (int i = 0; i < worker_nums; ++i) {
        int sockpipefd_pair[2];
        socketpair(AF_LOCAL, SOCK_STREAM, 0, sockpipefd_pair);
        pid_t pid = fork();
        if (pid == 0) {
            close(sockpipefd_pair[1]);
            worker_loop(sockpipefd_pair[0]);

        }
        else{
            close(sockpipefd_pair[0]);
            worker_data_arr[i].pid = pid;
            worker_data_arr[i].status = FREE;
            worker_data_arr[i].id= i;
            worker_data_arr[i].sockpipefd = sockpipefd_pair[1];
#ifdef LOG_DEBUG
            printf("create a worker, \
                    worker_id = %d, \
                    sockpipefd = %d\n", worker_data_arr[i].id, worker_data_arr[i].sockpipefd);
#endif /* ifdef LOG_DEBUG
          printf("create a worker,
          worker_id = %ld,
          sockpipefd = %d\n", worker_data_arr[i].) */
        }
    }
    return 0;
}

int worker_loop(int sockpipefd) {
    for (;;) {
    }
}
