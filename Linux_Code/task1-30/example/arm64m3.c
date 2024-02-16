#include <myselfc.h>

#define ADD_COUNT 100000

int main(void){
    int shm_id = shmget(0x10010, 4096, IPC_CREAT|0600);
    ERROR_CHECK(shm_id, -1, "shmget");
    int* nums = (int*)shmat(shm_id, NULL, 0);
    memset(nums, 0, 4096);
    if(fork()){
        for(int i = 0; i < ADD_COUNT; ++i){
            ++*nums;
        }

        wait(NULL);
        printf("sum = %d\n", *nums);
    }
    else{
        for(int i = 0; i < ADD_COUNT; ++i){
            ++*nums;
        }

    }
    return 0;
}
