// #include <iostream>
// using std::cout;
// using std::endl;
//
// class Func {
//   public:
//     static void print(int a) {
//         cout << a << endl;
//     }
// };
//
// int main( ) {
//     void (Func::*p1)(int) = std::mem_fn(&Func::print);
// }


#include <iostream>
using std::cout;
using std::endl;

class Func {
  public:
    void print(int a) {
        cout << a << endl;
    }
};

int main( ) {
    void (Func::*p1)(int) = &Func::print;

    Func a;

    void (Func::*p2)(int) = &Func::print;

    (a.*p1)(10); // 调用 print 函数

    return 0;
}
