#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timerfd.h>
#include <unistd.h>


static int __TimerFds[2];
static char __isLooping = 1;
static pthread_t __TimerFd_Thid;


int timerfd_create(clockid_t clock_id, int flags) {
    if (pipe(__TimerFds) == 0) { return __TimerFds[0]; }
    return -1;
}

int timerfd_gettime(int ufd, struct itimerspec *otmr) {
    return 0;
}

static void *timerfd_thread(void *arg) {
    struct itimerspec itimer;
    memcpy(&itimer, arg, sizeof(struct itimerspec));
    uint64_t timeouts = 0;

    nanosleep(&itimer.it_value, NULL);
    ++timeouts;
    write(__TimerFds[1], &timeouts, sizeof(timeouts));

    while (__isLooping) {
        nanosleep(&itimer.it_interval, NULL);
        ++timeouts;
        write(__TimerFds[1], &timeouts, sizeof(timeouts));
    }

    pthread_exit(NULL);
}

static void timerfd_cleanup(void) {
    __isLooping = 0;
    close(__TimerFds[0]);
    close(__TimerFds[1]);
    pthread_join(__TimerFd_Thid, NULL);
}

int timerfd_settime(int ufd, int flags, const struct itimerspec *utmr, struct itimerspec *otmr) {
    pthread_create(&__TimerFd_Thid, NULL, timerfd_thread, (void *)utmr);
    atexit(timerfd_cleanup);
    return 0;
}