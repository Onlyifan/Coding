#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

template <typename T> class MyTemplateClass {
  public:
    // 非静态数据成员
    T data;

    // 非静态成员函数模板
    template <typename U> void process(U value) {
        // 在这里，T 和 U 可以是任意类型，这个函数会处理传入的 U
        // 类型值，并可能操作 this->data
        data = static_cast<T>(
            value); // 示例操作：将传入的 value 转换为 T 类型并赋值给 data
    }

    // 具体的非模板成员函数
    void display( ) {
        std::cout << "Data is: " << data << std::endl;
    }
};

// 使用示例：
int main( ) {
    MyTemplateClass<double> obj;
    MyTemplateClass<double>( ).display( );
    obj.process(3.14); // 使用 double 类型实例化时，process 接受并处理一个
                       // double 类型的值
    obj.display( ); // 显示处理后的数据
    return 0;
}
