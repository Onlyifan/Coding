#include "producer.hh"
#include "task_queue.hh"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int ProducerFunc::func(TaskQueue &tq, int x) {
    ::srand(::time(nullptr));

    while (x--) {
        int value = rand( ) % 100;
        tq.push(value);
        std::cout << "producer push " << value << std::endl;
        // sleep(1);
    }

    return 0;
}
