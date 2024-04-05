#ifndef _CONDITION_HH_
#define _CONDITION_HH_


#include "noncopyable.hh"
#include <pthread.h>


class MutexLock;

class Condition : protected Noncopyable {
  public:
    Condition(MutexLock &);
    ~Condition( );

    void wait( );
    void notify( );
    void notifyAll( );


  private:
    MutexLock &_mutex;
    pthread_cond_t _cond;
};


#endif // _CONDITION_HH_
