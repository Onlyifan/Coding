/**
 * Project factorys
 */


#ifndef _FACTORY_H
#define _FACTORY_H

#include <memory>

class Figure;

enum FigureType { circle, rectangle };

class Factory {
  public:
    /**
     * @param type
     */
    static std::unique_ptr<Figure> create(FigureType type);
};

#endif //_FACTORY_H
