#include "thread_pool.hh"
#include <iostream>

using namespace std;

struct MyTask {
    void process(int x) { cout << x << endl; }
};

int main( ) {
    MyTask t;

    ThreadPool pl(3, 10);

    pl.strat( );
    for (int i = 0; i != 30; ++i) {
        pl.addTask(std::bind(&MyTask::process, &t, i));
    }

    pl.stop( );
}
