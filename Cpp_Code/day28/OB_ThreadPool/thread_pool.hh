#ifndef _THREAD_POOL_HH_
#define _THREAD_POOL_HH_


#include "task_queue.hh"
#include <memory>
#include <vector>

class Task;
class WorkThread;

class ThreadPool : protected Noncopyable {

  public:
    using Task = TaskQueue::taskType;
    ThreadPool(size_t threadNum, size_t taskQueNum);
    ~ThreadPool( ) = default;

    void start( );
    void stop( );

    void addTask(Task &&);
    Task fetchTask( );
    void doTask( );

  private:
    size_t _threadNum;
    std::vector<std::unique_ptr<WorkThread>> _threads;
    TaskQueue _queue;
    bool _isExit;
};


#endif // _THREAD_POOL_HH_
