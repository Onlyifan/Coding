#include <myselfc.h>

int main(void){
    int shm_id = shmget(0x10086, 40960, IPC_CREAT|0600);
    ERROR_CHECK(shm_id, -1, "shmget");
    printf("shm_id = %d\n", shm_id);
    char* pstr = (char*)shmat(shm_id, NULL, 0);
    ERROR_CHECK(*pstr, -1, "shmat");
    char sent[] = "How are you";
    memcpy(pstr, sent, strlen(sent));

    return 0;
}
