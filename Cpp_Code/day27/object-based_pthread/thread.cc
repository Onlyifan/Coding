#include "thread.hh"
#include <iostream>
#include <stdio.h>
#include <utility>

Thread::Thread(ThreadCallback &&cb)
    : _tcb(std::move(cb))
    , _isRunning(false) {}

void Thread::start( ) {
    if (!_isRunning) {
        int ret = ::pthread_create(&_pthId, nullptr, threadFunc, this);
        if (ret) {
            ::perror("pthread_create");
            return;
        }
        _isRunning = true;
    }
}

void Thread::stop( ) {
    if (_isRunning) {
        int ret = ::pthread_join(_pthId, nullptr);
        if (ret) {
            ::perror("pthread_join");
            return;
        }
        _isRunning = false;
    }
}

void *Thread::threadFunc(void *obj) {
    Thread *pTh = static_cast<Thread *>(obj);
    if (pTh == nullptr) {
        std::cerr << "ERROR: *Thread is nullptr in threadFunc" << std::endl;
    } else {
        pTh->_tcb( );
    }

    ::pthread_exit(nullptr);
}
