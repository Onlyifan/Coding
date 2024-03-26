#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

class Point {
  public:
    Point(int x = 114, int y = 233)
        : _x(x)
        , _y(y) {
        cout << "create" << endl;
    }

    Point(const Point &rhs)
        : _x(rhs._x)
        , _y(rhs._y) {
        cout << "kao bei" << endl;
    }

    Point(Point &&rhs)
        : _x(1)
        , _y(1) {
        cout << "move" << endl;
    }

  private:
    int _x;
    int _y;
};


int main(void) {
    vector<Point> vec;
    vec.push_back(Point(7, 8));


    return 0;
}
