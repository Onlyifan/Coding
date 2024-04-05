/**
 * Project factorys
 */


#ifndef _CIRCLE_H
#define _CIRCLE_H

#include "Figure.h"


class Circle : public Figure {
  public:
    Circle(double radius);
    void showType( );

    double area( );

  private:
    double _radius;
};

#endif //_CIRCLE_H
