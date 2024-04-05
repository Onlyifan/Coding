#include "consumer.hh"
#include "task_queue.hh"
#include <iostream>

int consumerFunc(TaskQueue &tq, int y) {
    while (y--) {
        std::cout << "consumer pop " << tq.pop( ) << std::endl;
    }

    return 0;
}
