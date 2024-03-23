#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;


#include <utility>

// 假设我们有一个大型结构体或类，这里简化为int
class BigObject {
  public:
    BigObject(int num)
        : value(num) {}

    int value;
    // 构造函数、析构函数、移动构造、移动赋值等在此省略...
};

// 工厂函数返回一个右值引用
BigObject &&createBigObject(int val) {
    BigObject obj{val};
    // 对象初始化完成
    // ...
    // 准备返回这个临时对象，因为它即将被销毁，适合移动而非复制
    // return std::move(obj);
    return obj;
}


int main(void) {
    const int &p = 1;
    int &&p2 = 1;


    // BigObject newObj(std::move(createBigObject(42)));
    // BigObject &&newObj(createBigObject(42));
    BigObject &&nnn = createBigObject(42);
    const BigObject &mmm = createBigObject(42);


    return 0;
}
