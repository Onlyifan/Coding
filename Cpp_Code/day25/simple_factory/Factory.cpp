/**
 * Project factorys
 */


#include "Factory.h"
#include "Circle.h"
#include "Figure.h"
#include "Rectangle.h"


/**
 * Factory implementation
 */


/**
 * @param type
 * @return unique_ptr<Figure>
 */
std::unique_ptr<Figure> Factory::create(FigureType type) {
    switch (type) {
    case rectangle:

        // 配置文件进行传递进来
        // txt、xml、yang
        // 读配置文件
        // 获取配置文件中的信息

        return std::unique_ptr<Rectangle>(new Rectangle(10, 20));
    case circle:
        return std::unique_ptr<Circle>(new Circle(10));
    }

    return nullptr;
}
