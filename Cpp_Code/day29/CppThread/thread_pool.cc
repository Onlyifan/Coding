#include "thread_pool.hh"
#include <chrono>

using namespace std;

ThreadPool::ThreadPool(size_t threadNum, size_t queSize)
    : _isExit(true)
    , _threadNums(threadNum)
    , _que(queSize) {
    _threads.reserve(_threadNums);
}


void ThreadPool::strat( ) {
    if (_isExit) {
        for (size_t i = 0; i != _threadNums; ++i) {
            _threads.emplace_back(&ThreadPool::doTask, this);
        }
        _isExit = false;
    }
}
void ThreadPool::stop( ) {
    if (_isExit == false) {

        while (!_que.isEmpty( )) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        _isExit = true;
        _que.wakeup( );

        for (auto &th : _threads) {
            th.join( );
        }
    }
}

void ThreadPool::addTask(TaskType &&task) {
    if (task) {
        _que.push(std::move(task));
    }
}

ThreadPool::TaskType ThreadPool::getTask( ) {
    return _que.pop( );
}

void ThreadPool::doTask( ) {

    while (!_isExit) {
        TaskType task = getTask( );

        if (task) {
            task( );
        }
    }
}
