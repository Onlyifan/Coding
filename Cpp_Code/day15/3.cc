#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;


double sum(void) {
    return 0;
}

template <typename T, typename... Args> double sum(T rhs, Args... args) {
    return rhs + sum(args...);
}


int main() {
    // 测试整数求和
    cout << "Sum of integers: " << sum(1, 2, 3, 4, 5) << endl;

    // 测试浮点数求和
    cout << "Sum of floating-point numbers: " << sum(1.5, 2.3, 3.7, 4.9) << endl;

    // 混合类型求和（由于返回值为 double 类型，所有整数会隐式转换为 double）
    cout << "Mixed types sum (integers and floats): " << sum(1, 2.5, 3, 4.3) << endl;

    return 0;
}
