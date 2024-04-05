#ifndef _PRODUCER_HH_
#define _PRODUCER_HH_

class TaskQueue;

struct ProducerFunc {
    int func(TaskQueue &tq, int x);
};


#endif // _PRODUCER_HH_
