/**
 * Project factorys
 */


#ifndef _FIGURE_H
#define _FIGURE_H

class Figure {
  public:
    virtual void showType( ) = 0;

    virtual double area( ) = 0;

    virtual ~Figure( ){ };
};

#endif //_FIGURE_H
