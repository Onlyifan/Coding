#ifndef _MUTEX_LOCK_HH_
#define _MUTEX_LOCK_HH_


#include "noncopyable.hh"
#include <pthread.h>

class MutexLock : protected Noncopyable {
    friend class Condition;

  public:
    MutexLock( );
    ~MutexLock( );

    void lock( );
    void trylock( );
    void unlock( );

  public:
    class MutexLockProxy {
      public:
        MutexLockProxy(MutexLock &mL);
        ~MutexLockProxy( );

      private:
        MutexLock &_mutexProxy;
    };


  private:
    pthread_mutex_t _mutex;
};


#endif // _MUTEX_LOCK_HH_
