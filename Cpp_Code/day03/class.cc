#include <iostream>
using std::cout;
using std::endl;


struct Point{

    private:
        int x = 10;
        int y = 10;
};





int main(void){
    Point dot(1, 2);
    dot.~Point();
    dot.~Point();
    dot.~Point();
    dot.~Point();
    dot.~Point();
    dot.~Point();
    dot.~Point();
    cout << "hello" << endl;
    
    return 0;
}
