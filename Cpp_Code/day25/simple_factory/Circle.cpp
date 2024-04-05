/**
 * Project factorys
 */


#include "Circle.h"
#include <iostream>
/**
 * Circle implementation
 */
Circle::Circle(double r)
    : _radius(r) {}


/**
 * @return void
 */
void Circle::showType( ) {
    std::cout << "Circle";
    return;
}

/**
 * @return double
 */
double Circle::area( ) {
    return 3.14 * _radius * _radius;
}
