#include "work_thread.hh"
#include "thread_pool.hh"
#include <iostream>
#include <stdio.h>


WorkThread::WorkThread(WorkThread::ThreadCallback &&cb)
    : _cb(std::move(cb))
    , _isRunning(false) {}

void WorkThread::start( ) {
    if (!_isRunning) {
        int ret = ::pthread_create(&_pthId, nullptr, threadFunc, this);
        if (ret) {
            ::perror("pthread_create");
            return;
        }
        _isRunning = true;
    }
}

void WorkThread::stop( ) {
    if (_isRunning) {
        int ret = ::pthread_join(_pthId, nullptr);
        if (ret) {
            ::perror("pthread_join");
            return;
        }
        _isRunning = false;
    }
}

void *WorkThread::threadFunc(void *obj) {
    WorkThread *pTh = static_cast<WorkThread *>(obj);
    if (pTh == nullptr) {
        std::cerr << "ERROR: *WorkThread is nullptr in threadFunc" << std::endl;
    } else {
        pTh->_cb( );
    }

    ::pthread_exit(nullptr);
}
