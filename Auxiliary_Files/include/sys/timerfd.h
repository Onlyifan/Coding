#ifndef _TIMERFD_H_
#define _TIMERFD_H_


#include <time.h>


struct itimerspec {
    struct timespec it_interval;
    struct timespec it_value;
};

#ifdef __cplusplus
extern "C" {
#endif

extern int timerfd_create(clockid_t clock_id, int flags);
extern int timerfd_settime(int ufd, int flags, const struct itimerspec *utmr, struct itimerspec *otmr);
extern int timerfd_gettime(int ufd, struct itimerspec *otmr);

#ifdef __cplusplus
}
#endif


#endif // _TIMERFD_H_
