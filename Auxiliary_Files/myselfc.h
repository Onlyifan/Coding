#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <syslog.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <sys/event.h>

#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

#include <pthread.h>

#define ARR_LEN(arr) (sizeof(arr) / sizeof(arr[0]))

#define ARGS_CHECK(argc,num) {if(argc!=num){fprintf(stderr,"args error!\n");return -1;}}
#define ERROR_CHECK(ret,num,msg) {if(ret==num){perror(msg); return -1;}}
#define THREAD_ERROR_CHECK(ret,msg) {if(ret!=0){fprintf(stderr,"%s:%s\n",msg,strerror(ret));}};




typedef union epoll_data {
    void *ptr;
    int fd;
    uint32_t u32;
    uint64_t u64;
} epoll_data_t;

typedef struct epoll_event {
    uint32_t events;
    epoll_data_t data;
} epoll_event;

#define EPOLL_CTL_ADD 1
#define EPOLL_CTL_DEL 2
#define EPOLL_CTL_MOD 3

#define EPOLLIN      0x001
#define EPOLLOUT     0x002
#define EPOLLPRI     0x004
#define EPOLLERR     0x008
#define EPOLLHUP     0x010
#define EPOLLET      0x020
#define EPOLLONESHOT 0x040
#define EPOLLRDNORM  0x040
#define EPOLLRDBAND  0x080
#define EPOLLWRNORM  0x100
#define EPOLLWRBAND  0x200
#define EPOLLMSG     0x400

int epoll_create(int size) {
    if(size <= 0){
        return -1;
    }
    return kqueue();
}

int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event) {
    struct kevent ke;
    int flags = 0;

    if (op == EPOLL_CTL_ADD) {
        if (event->events & EPOLLIN) {
            EV_SET(&ke, fd, EVFILT_READ, EV_ADD | EV_ENABLE | (event->events & EPOLLET ? EV_CLEAR : 0), 0, 0, event->data.ptr);
            kevent(epfd, &ke, 1, NULL, 0, NULL);
        }
        if (event->events & EPOLLOUT) {
            EV_SET(&ke, fd, EVFILT_WRITE, EV_ADD | EV_ENABLE | (event->events & EPOLLET ? EV_CLEAR : 0), 0, 0, event->data.ptr);
            kevent(epfd, &ke, 1, NULL, 0, NULL);
        }
    } else if (op == EPOLL_CTL_DEL) {
        EV_SET(&ke, fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
        kevent(epfd, &ke, 1, NULL, 0, NULL);
        EV_SET(&ke, fd, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
        kevent(epfd, &ke, 1, NULL, 0, NULL);
    } else if (op == EPOLL_CTL_MOD) {
        if (event->events & EPOLLIN) {
            EV_SET(&ke, fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
            kevent(epfd, &ke, 1, NULL, 0, NULL);
            EV_SET(&ke, fd, EVFILT_READ, EV_ADD | EV_ENABLE | (event->events & EPOLLET ? EV_CLEAR : 0), 0, 0, event->data.ptr);
            kevent(epfd, &ke, 1, NULL, 0, NULL);
        }
        if (event->events & EPOLLOUT) {
            EV_SET(&ke, fd, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
            kevent(epfd, &ke, 1, NULL, 0, NULL);
            EV_SET(&ke, fd, EVFILT_WRITE, EV_ADD | EV_ENABLE | (event->events & EPOLLET ? EV_CLEAR : 0), 0, 0, event->data.ptr);
            kevent(epfd, &ke, 1, NULL, 0, NULL);
        }
    }

    return 0;
}

int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout) {
    struct kevent kevents[maxevents];
    struct timespec ts;
    int nevents;

    // 如果 timeout 小于 0，表示无限期等待
    if (timeout >= 0) {
        ts.tv_sec = timeout / 1000; // 秒数
        ts.tv_nsec = (timeout % 1000) * 1000000; // 纳秒数
    }

    // 调用 kevent
    nevents = kevent(epfd, NULL, 0, kevents, maxevents, timeout >= 0 ? &ts : NULL);

    // 将 kevent 返回的事件转换为 epoll_event
    for (int i = 0; i < nevents; ++i) {
        struct epoll_event *e = &events[i];
        e->data.fd = kevents[i].ident;
        e->events = 0;

        if (kevents[i].filter == EVFILT_READ) {
            e->events |= EPOLLIN;
        } else if (kevents[i].filter == EVFILT_WRITE) {
            e->events |= EPOLLOUT;
        }

        if (kevents[i].flags & EV_ERROR) {
            e->events |= EPOLLERR;
        }
        if (kevents[i].flags & EV_EOF) {
            e->events |= EPOLLHUP;
        }
    }

    return nevents;
}
