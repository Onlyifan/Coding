#include "task_queue.hh"

TaskQueue::TaskQueue(size_t capacity)
    : _capacity(capacity)
    , _isExit(false)
    , _taskQueue( )
    , _mutex( )
    , _notFull(_mutex)
    , _notEmpty(_mutex) {}

bool TaskQueue::isFull( ) {
    return _capacity == _taskQueue.size( );
}
bool TaskQueue::isEmpty( ) {
    return 0 == _taskQueue.size( );
}

void TaskQueue::push(TaskQueue::taskType &&pTask) {
    MutexLock::MutexLockProxy autoLock(_mutex);
    while (isFull( )) {
        _notFull.wait( );
    }
    _taskQueue.push(std::move(pTask));
    _notEmpty.notify( );
}

TaskQueue::taskType TaskQueue::pop( ) {
    taskType result;
    {
        MutexLock::MutexLockProxy autoLock(_mutex);
        while (isEmpty( ) && !_isExit) {
            _notEmpty.wait( );
        }
        if (_isExit) {
            return []( ) -> int { return 0; };
        }
        result = _taskQueue.front( );
        _taskQueue.pop( );
        _notFull.notify( );
    }

    return result;
}

void TaskQueue::wakeup( ) {
    _isExit = true;
    _notEmpty.notifyAll( );
}
