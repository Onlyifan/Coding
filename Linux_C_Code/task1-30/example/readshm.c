#include <myselfc.h>

int main(void){
    int shm_id = shmget(0x10086, 40960, IPC_CREAT|0600);
    ERROR_CHECK(shm_id, -1, "shmget");

    char* pstr = (char*)shmat(shm_id, NULL, 0);
    printf("%s\n", pstr);
    return 0;
}
