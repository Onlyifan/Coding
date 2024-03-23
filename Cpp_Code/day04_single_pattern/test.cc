#include <iostream>
using std::cout;
using std::endl;

class Small{
    private:
        int a;
        int b;
};

class MyClass {
    public:
        MyClass(int x)
            :_x(x)
    {}
        MyClass & operator = (const MyClass & rhs)
        {
            return *this;
        }
        int add(const int * const aa);
        int add(int * const aa);

    private:
        int _x;
};


int main(void){
    MyClass *pstu = new MyClass[2]{1,2};
    MyClass *pst1 = new MyClass[2]{{1}, {2}};

    int a = 10;
    int b = 20;
    int c = 30;
    a = a = b = c;
    cout << a << b << c << endl;
    
    return 0;
}
