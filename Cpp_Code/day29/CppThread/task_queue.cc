#include "task_queue.h"

using namespace std;

TaskQueue::TaskQueue(size_t capacity)
    : _capacity(capacity)
    , _isRunning(true) {}

bool TaskQueue::isFull( ) const {
    return _queue.size( ) == _capacity;
}

bool TaskQueue::isEmpty( ) const {
    return _queue.size( ) == 0;
}

void TaskQueue::push(ElemType &&task) {
    unique_lock<mutex> autoLock(_mutex);
    while (isFull( )) {
        _notFull.wait(autoLock);
    }

    _queue.push(std::move(task));
    _notEmpty.notify_one( );
}


TaskQueue::ElemType TaskQueue::pop( ) {
    unique_lock<mutex> autoLock(_mutex);

    while (isEmpty( ) && _isRunning) {
        _notEmpty.wait(autoLock);
    }

    if (!_isRunning) {
        return nullptr;
    }

    ElemType elem = _queue.front( );
    _queue.pop( );

    _notFull.notify_one( );

    return elem;
}
void TaskQueue::wakeup( ) {
    _isRunning = false;

    _notEmpty.notify_all( );
}
