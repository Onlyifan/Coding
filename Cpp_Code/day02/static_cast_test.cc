#include <iostream>
#include <myselfc.h>

int main(void){
    const char *pstr = "hello";
    int *p = static_cast<int*>(pstr);
    ERROR_CHECK()
    
    return 0;
}
