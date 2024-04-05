#ifndef _TASK_QUEUE_HH_
#define _TASK_QUEUE_HH_

#include "condition.hh"
#include "mutex_lock.hh"
#include "noncopyable.hh"
#include <queue>

class TaskQueue : protected Noncopyable {
  public:
    TaskQueue(size_t capacity);
    ~TaskQueue( ) = default;

    void push(int value);
    int pop( );

    bool isEmpty( );
    bool isFull( );

  private:
    


  private:
    std::size_t _capacity;
    std::queue<int> _taskQueue;
    MutexLock _mutex;
    Condition _notFull;
    Condition _notEmpty;
};


#endif // _TASK_QUEUE_HH_
