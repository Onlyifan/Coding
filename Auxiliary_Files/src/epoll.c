#include <errno.h>
#include <stdio.h>
#include <sys/epoll.h>
#include <time.h>


int epoll_create(int size) {
    return kqueue( );
}
int epoll_create1(int flags) {
    return kqueue( );
}

int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event) {
    struct kevent kev[2];

    if ((!event && op != EPOLL_CTL_DEL) ||
        (op != EPOLL_CTL_ADD && op != EPOLL_CTL_MOD && op != EPOLL_CTL_DEL)) {
        errno = EINVAL;
        EV_ENABLE;
        return -1;
    }

    switch (op) {
    case EPOLL_CTL_ADD:
        if (event->events & EPOLLIN) {
            EV_SET(kev, fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, event->data.ptr);
            kevent(epfd, kev, 1, NULL, 0, NULL);
        }
        if (event->events & EPOLLOUT) {
            EV_SET(kev, fd, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, event->data.ptr);
            kevent(epfd, kev, 1, NULL, 0, NULL);
        }
        return 0;

    case EPOLL_CTL_DEL:
        EV_SET(kev, fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
        EV_SET(kev + 1, fd, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
        break;

    case EPOLL_CTL_MOD:
        EV_SET(kev, fd, EVFILT_READ, EV_ADD | (event->events & EPOLLIN ? EV_ENABLE : EV_DISABLE), 0,
               0, event->data.ptr);
        EV_SET(kev + 1, fd, EVFILT_WRITE,
               EV_ADD | (event->events & EPOLLOUT ? EV_ENABLE : EV_DISABLE), 0, 0, event->data.ptr);
        break;
    }

    kevent(epfd, kev, 2, NULL, 0, NULL);
    return 0;
}

int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout) {
    if (!events || maxevents < 1) {
        errno = EINVAL;
        return -1;
    }

    struct timespec ts;
    if (timeout >= 0) {
        ts.tv_sec = timeout / 1000;
        ts.tv_nsec = (timeout % 1000) * 1000000;
    }

    int ready_events =
        kevent(epfd, NULL, 0, (struct kevent *)events, maxevents, timeout >= 0 ? &ts : NULL);

    for (int i = 0; i != ready_events; ++i) {
        if (EVFILT_READ == ((struct kevent *)(events + i))->filter) {
            events[i].events = EPOLLIN;
        } else if (EVFILT_WRITE == ((struct kevent *)(events + i))->filter) {
            events[i].events = EPOLLOUT;
        }
        events[i].data.ptr = ((struct kevent *)(events + i))->udata;
    }

    return ready_events;
}
