#include "task_queue.hh"

TaskQueue::TaskQueue(size_t capacity)
    : _capacity(capacity)
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

void TaskQueue::push(int value) {
    MutexLock::MutexLockProxy autoLock(_mutex);
    while (isFull( )) {
        _notFull.wait( );
    }
    _taskQueue.push(value);
    _notEmpty.notify( );
}

int TaskQueue::pop( ) {
    int result;
    {
        MutexLock::MutexLockProxy autoLock(_mutex);
        while (isEmpty( )) {
            _notEmpty.wait( );
        }
        result = _taskQueue.front( );
        _taskQueue.pop( );
        _notFull.notify( );
    }

    return result;
}
