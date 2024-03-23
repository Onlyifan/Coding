#include <iostream>
using std::cout;
using std::endl;

class Point;

class Complex {
  public:
    Complex(int real = 1, int image = 2)
        : _real(real)
        , _image(image) {}

    // Complex(Point &ptconst Complex &operator=(CONST Point &rhs) const {

    void operator=(Point &rhs) {}

    void print( ) const {
        cout << _real << "+" << _image << "i" << endl;
    }

  private:
    int _real;
    int _image;
};

class Point {
  public:
    explicit Point(int x = 0, int y = 0)
        : _ix(x)
        , _iy(y) {
        cout << "Point (int,int)" << endl;
    }

    void print( ) const {
        cout << "(" << _ix << "," << _iy << ")" << endl;
    }

    operator int( ) {
        cout << "operator int()" << endl;
        return _ix + _iy;
    }

    operator Complex( ) {
        cout << "operator Complex()" << endl;
        return Complex(_ix, _iy);
    }

    friend class Complex;

  private:
    int _ix;
    int _iy;
};


// Complex::Complex(Point &rhs)
//     : _real(rhs._ix)
//     , _image(rhs._iy) {
//     cout << "Complex(Point &rhs)" << endl;
// }

void test0( ) {
    // 隐式转换，从内置类型转换成自定义类型
    /* Point pt = 1; */

    Point pt2(1, 2);
    // 利用类型转换函数，将自定义类型转换成了内置类型
    int a = pt2;
    int b = pt2.operator int( ); // 本质
    cout << a << endl;
    cout << b << endl;
}

void test1( ) {
    Point pt(1, 2);
    Complex cx(3, 4);


    // 隐式转换，cx = Complex(pt);
    cx = pt;
    cx.print( );
}

int main(void) {
    test1( );
    return 0;
}
