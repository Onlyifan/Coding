/**
 * Project factorys
 */


#include "Rectangle.h"
#include <iostream>


/**
 * Rectangle implementation
 */


/**
 * @return void
 */
void Rectangle::showType( ) {
    std::cout << "Rectangle";
    return;
}

/**
 * @return double
 */
double Rectangle::area( ) {
    return _width * _length;
}
