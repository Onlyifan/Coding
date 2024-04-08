#ifndef _THREAD_POOL_HH_
#define _THREAD_POOL_HH_


#include "noncopyable.hh"
#include "task_queue.h"
#include <cstddef>
#include <thread>
#include <vector>

class ThreadPool : protected Noncopyable {
  public:
    using TaskType = TaskQueue::ElemType;


    ThreadPool(size_t thradNum, size_t queSize);
    ~ThreadPool( ) = default;

    void strat( );
    void stop( );

    void addTask(TaskType &&task);

  private:
    TaskType getTask( );
    void doTask( );


  private:
    bool _isExit;
    std::size_t _threadNums;
    TaskQueue _que;
    std::vector<std::thread> _threads;
};


#endif // _THREAD_POOL_HH_
