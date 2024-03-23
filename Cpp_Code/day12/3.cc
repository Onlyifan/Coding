#include <iostream>
#include <math.h>
using std::cout;
using std::endl;

class Circle {
  public:
    Circle( )
        : _r(0.0) {}
    Circle(double r)
        : _r(r) {}

    double getArea( ) {
        return pow(_r, 2) * M_PI;
    }

    double getPerimeter( ) {
        return _r * 2 * M_PI;
    }

    void show( ) {
        cout << "Circle's area is " << getArea( ) << ", perimeter is "
             << getPerimeter( ) << ", radius is " << _r << "." << endl;
    }

  private:
    double _r;
};

int main(void) {

    Circle c1;
    c1.show( );

    Circle c2(1);
    c2.show( );


    return 0;
}
