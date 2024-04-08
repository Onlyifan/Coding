#include "thread_pool.hh"
#include "work_thread.hh"
#include <iostream>
#include <memory>
#include <unistd.h>

ThreadPool::ThreadPool(size_t threadNum, size_t taskQueNum)
    : _threadNum(threadNum)
    , _threads( )
    , _queue(taskQueNum)
    , _isExit(true) {

    _threads.reserve(_threadNum);
}

void ThreadPool::start( ) {
    if (_isExit == true) {
        for (size_t i = 0; i != _threadNum; ++i) {
            _threads.emplace_back(
                std::unique_ptr<WorkThread>(new WorkThread(std::bind(&ThreadPool::doTask, this))));

            _threads.emplace_back(
                new WorkThread(std::bind(&ThreadPool::doTask, this)));
            // _threads.push_back(std::make_unique<WorkThread>(std::bind(&ThreadPool::doTask,
            // this)));
        }

        _isExit = false;

        for (auto &th : _threads) {
            th->start( );
        }
    }
}

void ThreadPool::stop( ) {
    if (_isExit == false) {

        while (!_queue.isEmpty( )) {
            ::sleep(1);
        }

        _isExit = true;

        ::sleep(2);

        _queue.wakeup( );

        for (auto &th : _threads) {
            th->stop( );
        }
    }
}

void ThreadPool::addTask(ThreadPool::Task &&task) {
    _queue.push(std::move(task));
}

ThreadPool::Task ThreadPool::fetchTask( ) {
    return _queue.pop( );
}

void ThreadPool::doTask( ) {
    while (!_isExit) {
        Task pTask = fetchTask( );
        if (pTask) {
            pTask( );
        } else {
            std::cerr << "pTask is error" << std::endl;
        }
    }
}
