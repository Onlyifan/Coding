/**
 * Project factorys
 */


#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#include "Figure.h"


class Rectangle : public Figure {
  public:
    Rectangle(double a, double b)
        : _length(a)
        , _width(b) {}
    void showType( );

    double area( );

  private:
    double _length;
    double _width;
};

#endif //_RECTANGLE_H
