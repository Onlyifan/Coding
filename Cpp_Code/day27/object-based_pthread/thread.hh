#ifndef _THREAD_HH_
#define _THREAD_HH_


#include "noncopyable.hh"
#include <functional>
#include <pthread.h>

class Thread : protected Noncopyable {
    using ThreadCallback = std::function<int( )>;

  public:
    Thread(ThreadCallback &&cb);
    void start( );

    void stop( );

  private:
    static void *threadFunc(void *);

  private:
    ThreadCallback _tcb;
    bool _isRunning;
    pthread_t _pthId;
};


#endif // _THREAD_HH_
