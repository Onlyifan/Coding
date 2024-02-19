#include <myselfc.h>
#include "process_pool.h"

int main(int argc, char *argv[]){
    // ./main server_ip port worker_nums
    ARGS_CHECK(argc, 4);

    int worker_nums = atoi(argv[3]);
    worker_data_t *worker_data_arr = (worker_data_t *)calloc(worker_nums, sizeof(worker_data_t));

    worker_create(worker_nums, worker_data_arr);
    
    
    
    
    return 0;
}
