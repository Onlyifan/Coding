#ifndef _THREAD_HH_
#define _THREAD_HH_


#include "noncopyable.hh"
#include <functional>
#include <pthread.h>


class ThreadPool;

class WorkThread : protected Noncopyable {
  private:
    using ThreadCallback = std::function<void( )>;


  public:
    WorkThread(ThreadCallback &&);
    ~WorkThread( ) = default;

    void start( );

    void stop( );

  private:
    static void *threadFunc(void *);

  private:
    ThreadCallback _cb;
    bool _isRunning;
    pthread_t _pthId;
};


#endif // _THREAD_HH_
