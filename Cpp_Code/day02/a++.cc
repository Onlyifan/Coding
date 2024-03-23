#include <iostream>
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main(void){
    int i = 1;
    int ret = MAX(i++, 2);
    
    return 0;
}
