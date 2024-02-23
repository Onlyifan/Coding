#include "process_pool.h"

int sendfd(int sockpipefd, int fd_to_send, bool exit_flag) {
    struct msghdr header;
    memset(&header, 0, sizeof(header));

    // 正文部分
    struct iovec vec[1];
    vec[0].iov_base = &exit_flag;
    vec[0].iov_len = sizeof(exit_flag);

    header.msg_iov = vec;
    header.msg_iovlen = ARR_LEN(vec);

    // 控制部分
    struct cmsghdr *p_cmsg = 
        (struct cmsghdr *)malloc(CMSG_LEN(sizeof(fd_to_send)));
    p_cmsg->cmsg_len = CMSG_LEN(sizeof(fd_to_send));
    p_cmsg->cmsg_type = SCM_RIGHTS;
    p_cmsg->cmsg_level = SOL_SOCKET;
    *(int *)CMSG_DATA(p_cmsg) = fd_to_send;

    header.msg_control = p_cmsg;
    header.msg_controllen = CMSG_LEN(sizeof(fd_to_send));

    int ret = sendmsg(sockpipefd, &header, 0);
    ERROR_CHECK(ret, -1, "sendfd");

    return 0;
}

int recvfd(int sockpipefd, int *p_fd_to_recv, bool *p_exit_flag) {
    struct msghdr header;
    memset(&header, 0, sizeof(header));

    // 正文部分
    struct iovec vec[1];
    vec[0].iov_base = p_exit_flag;
    vec[0].iov_len = sizeof(*p_exit_flag);

    header.msg_iov = vec;
    header.msg_iovlen = ARR_LEN(vec);

    // 控制部分
    struct cmsghdr *p_cmsg = 
        (struct cmsghdr *)malloc(CMSG_LEN(*p_fd_to_recv));
    p_cmsg->cmsg_len = CMSG_LEN(sizeof(*p_fd_to_recv));
    p_cmsg->cmsg_type = SCM_RIGHTS;
    p_cmsg->cmsg_level = SOL_SOCKET;

    header.msg_control = p_cmsg;
    header.msg_controllen = CMSG_LEN(sizeof(*p_fd_to_recv));

    int ret = recvmsg(sockpipefd, &header, 0);
    ERROR_CHECK(ret, -1, "sendfd");

    *p_fd_to_recv = *(int *)CMSG_DATA(p_cmsg);

    printf("exit_flag = %d, fd = %d\n", *p_exit_flag, 
            *(int *)CMSG_DATA(p_cmsg));

    return 0;
}
