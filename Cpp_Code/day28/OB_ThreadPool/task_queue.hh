#ifndef _TASK_QUEUE_HH_
#define _TASK_QUEUE_HH_

#include "condition.hh"
#include "mutex_lock.hh"
#include "noncopyable.hh"
#include <queue>


class TaskQueue : protected Noncopyable {

  public:
    // using taskType = std::shared_ptr<std::function<int( )>>;
    using taskType = std::function<int( )>;
    TaskQueue(size_t capacity);
    ~TaskQueue( ) = default;


    void push(taskType &&);
    taskType pop( );

    void wakeup( );

    bool isEmpty( );

  private:
    bool isFull( );


  private:
    std::size_t _capacity;
    bool _isExit;
    std::queue<taskType> _taskQueue;
    MutexLock _mutex;
    Condition _notFull;
    Condition _notEmpty;
};


#endif // _TASK_QUEUE_HH_
