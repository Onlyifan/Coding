#include <iostream>
using std::cout;
using std::endl;

class Point;

class Complex {
  public:
    Complex(int real = 1, int image = 2)
        : _real(real)
        , _image(image) {}

    Complex(const Point &pt);

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
        cout << "Point(int,int)" << endl;
    }

    void print( ) const {
        cout << "(" << _ix << "," << _iy << ")" << endl;
    }

    // operator Complex( ) {
    //     cout << "operator Complex()" << endl;
    //     return Complex(_ix, _iy);
    // }

    friend class Complex;

  private:
    int _ix;
    int _iy;
};

Complex::Complex(const Point &rhs)
    : _real(rhs._ix)
    , _image(rhs._iy) {
    cout << "Complex(Point &rhs)" << endl;
}

void test1( ) {
    const Point pt(1, 2);
    Complex cx(3, 4);

    // 隐式转换，cx = Complex(pt);
    cx = pt;
    cx.print( );
}

int main(void) {
    test1( );
    return 0;
}
