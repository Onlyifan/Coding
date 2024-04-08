#ifndef _TASK_QUEUE_H_
#define _TASK_QUEUE_H_

#include "noncopyable.hh"
#include <condition_variable>
#include <cstddef>
#include <functional>
#include <mutex>
#include <queue>

class TaskQueue : protected Noncopyable {
  public:
    using ElemType = std::function<void( )>;

  public:
    TaskQueue(std::size_t capacity);
    ~TaskQueue( ) = default;

    void push(ElemType &&task);
    ElemType pop( );
    void wakeup( );

    bool isFull( ) const;
    bool isEmpty( ) const;


  private:
    std::size_t _capacity;
    bool _isRunning;
    std::queue<ElemType> _queue;
    std::mutex _mutex;
    std::condition_variable _notFull;
    std::condition_variable _notEmpty;
};


#endif // _TASK_QUEUE_H_
