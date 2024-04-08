#ifndef _CONDITION_H_
#define _CONDITION_H_


#include <pthread.h>


class Condition {

  public:
    Condition( );

  private:
    pthread_mutex_t &_mutex;
    pthread_cond_t _cond;
};


#endif // _CONDITION_H_
