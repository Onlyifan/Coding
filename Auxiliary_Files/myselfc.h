#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>
#include <syslog.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>
#include <dirent.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#define ARR_LEN(arr) (sizeof(arr) / sizeof(arr[0]))
#define ARGS_CHECK(argc,num) {if(argc!=num){fprintf(stderr,"args error!\n");return -1;}}
#define ERROR_CHECK(ret,num,msg) {if(ret==num){perror(msg); return -1;}}
#define THREAD_ERROR_CHECK(ret,msg) {if(ret!=0){fprintf(stderr,"%s:%s\n",msg,strerror(ret));}};


#ifdef __linux__
#include <sys/epoll.h>
#endif // __linux___ 

#ifdef __APPLE__
#include <sys/event.h>
// Epoll events
#define EPOLLIN        0x001
#define EPOLLPRI       0x002
#define EPOLLOUT       0x004
#define EPOLLRDNORM    0x040
#define EPOLLRDBAND    0x080
#define EPOLLWRNORM    0x100
#define EPOLLWRBAND    0x200
#define EPOLLMSG       0x400
#define EPOLLERR       0x008
#define EPOLLHUP       0x010
#define EPOLLET        0x80000000
#define EPOLLONESHOT   0x40000000
#define EPOLLEXCLUSIVE 0x10000000

// Epoll_ctl operations
#define EPOLL_CTL_ADD  1
#define EPOLL_CTL_DEL  2
#define EPOLL_CTL_MOD  3

typedef union epoll_data {
    void *ptr;     /* Pointer to user data */
    int fd;        /* File descriptor (for level-triggered I/O) */
    uint32_t u32;  /* Generic 32-bit data type */
    uint64_t u64;  /* Generic 64-bit data type */
} epoll_data_t;

struct epoll_event {
    uint32_t events; /* Epoll events */
    epoll_data_t data; /* User data variable */
};

// Function prototypes
int epoll_create(int size);
int epoll_ctl(int kq, int op, int fd, struct epoll_event *event);
int epoll_wait(int kq, struct epoll_event *events, int max_events, int timeout);

// 辅助函数：将kevent的udata转换为epoll_event.data
static inline void convert_kevent_to_epoll(struct kevent *kev, struct epoll_event *ev) {
    ev->events = kev->fflags;
    ev->data.ptr = kev->udata;
}

// 模拟epoll_create
int epoll_create(int size) {
    int kq = kqueue();
    if (kq == -1) {
        perror("kqueue");
        exit(EXIT_FAILURE);
    }
    return kq;
}

// 模拟epoll_ctl
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event) {
    struct kevent kev;

    switch (op) {
        case EPOLL_CTL_ADD:
            EV_SET(&kev, fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, event->data.ptr); // 使用用户数据
            if (event->events & EPOLLET) { // 边缘触发（Edge Triggered）
                kev.flags |= EV_CLEAR; // 需要手动清理事件状态
            }
            break;
        case EPOLL_CTL_MOD:
            // 在kqueue中，修改监听事件通常需要先删除再添加
            epoll_ctl(epfd, EPOLL_CTL_DEL, fd, event);
            EV_SET(&kev, fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, event->data.ptr);
            break;
        case EPOLL_CTL_DEL:
            EV_SET(&kev, fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
            break;
        default:
            errno = EINVAL;
            return -1;
    }

    ERROR_CHECK(kevent(epfd, &kev, 1, NULL, 0, NULL), -1, "kevent");
    return 0;
}

// 模拟epoll_wait
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout) {
    struct timespec ts;
    if (timeout >= 0) {
        ts.tv_sec = timeout / 1000;
        ts.tv_nsec = (timeout % 1000) * 1000000;
    }

    int num_events = kevent(epfd, NULL, 0, (struct kevent *)events, maxevents, timeout >= 0 ? &ts : NULL);
    ERROR_CHECK(num_events, -1, "kevent");

    for (int i = 0; i < num_events; ++i) {
        convert_kevent_to_epoll((struct kevent *)&events[i], &events[i]);
    }

    return num_events;
}

#endif // __APPLE__
