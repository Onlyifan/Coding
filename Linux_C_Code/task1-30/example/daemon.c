#include <myselfc.h>

#define DEVICE_COUNT 64

int daemonize(void){

    if(fork()){
        exit(0);
    }
    else{
        // 创建新会话并成为组长
        pid_t ret_sid = setsid();
        ERROR_CHECK(ret_sid, -1, "setsid");

        // 关闭设备
        for(int i = 0; i < DEVICE_COUNT; ++i){
            close(i);
        }

        // 改变属性
        int ret_chdir = chdir("/");
        ERROR_CHECK(ret_chdir, -1, "chdir");
        umask(0);
    }

    return 0;
}

int main(void){

    daemonize();

    for(int i = 0; i < 50; ++i){
        syslog(LOG_INFO, "i am demon %d\n", i);
        sleep(3);
    }
    return 0;
}
