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

class Cylinder : public Circle {
  public:
    Cylinder(double r, double h)
        : Circle(r)
        , _h(h) {}

    double getVolume( ) {
        return getArea( ) * _h;
    }

    void showVolume( ) {
        cout << "Cylinder's volume is " << getVolume( ) << "." << endl;
    }


  private:
    double _h;
};

int main(void) {
    Cylinder cy1(1, 1);
    cy1.show( );
    cy1.showVolume( );

    return 0;
}
