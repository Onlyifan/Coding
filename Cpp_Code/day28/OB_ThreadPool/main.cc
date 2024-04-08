#include "thread_pool.hh"
#include "work_thread.hh"
#include <functional>
#include <iostream>
#include <time.h>

using std::cout;
using std::endl;


int process(int x) {
    ::srand(::clock( ));

    int value = rand( ) % 100;
    std::cout << "process(" << x << ") push " << value << std::endl;

    return 0;
}


void test( ) {
    ThreadPool thPool(3, 10);

    thPool.start( );

    for (size_t i = 0; i != 20; ++i) {
        thPool.addTask(std::bind(process, 1));
    }

    thPool.stop( );
}

int main(void) {
    test( );


    return 0;
}
