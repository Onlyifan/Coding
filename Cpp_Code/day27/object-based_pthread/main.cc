#include "consumer.hh"
#include "producer.hh"
#include "task_queue.hh"
#include "thread.hh"
#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;


void test( ) {
    TaskQueue taskQue(10);
    ProducerFunc p;
    unique_ptr<Thread> producer1(
        std::make_unique<Thread>(std::bind(&ProducerFunc::func, &p, std::ref(taskQue), 15)));

    unique_ptr<Thread> consumer1(
        std::make_unique<Thread>(std::bind(&consumerFunc, std::ref(taskQue), 15)));


    producer1->start( );
    consumer1->start( );
    producer1->stop( );
    consumer1->stop( );
}

int main(void) {
    test( );


    return 0;
}
