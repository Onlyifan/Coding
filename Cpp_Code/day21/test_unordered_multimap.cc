#include <iostream>
#include <math.h>
#include <unordered_map>

using std::cout;
using std::endl;
using std::unordered_multimap;

template <typename Container> void display(const Container &con) {
    // for (auto &elem : con) {
    // cout << elem << "   ";
    // }
    cout << endl;
}

class Point {
  public:
    Point(int ix = 0, int iy = 0)
        : _ix(ix)
        , _iy(iy) {}

    float getDistance( ) const {
        return hypot(_ix, _iy);
    }

    int getX( ) const {
        return _ix;
    }

    int getY( ) const {
        return _iy;
    }

    ~Point( ) {}

    friend std::ostream &operator<<(std::ostream &os, const Point &rhs);

  private:
    int _ix;
    int _iy;
};

std::ostream &operator<<(std::ostream &os, const Point &rhs) {
    os << "(" << rhs._ix << ", " << rhs._iy << ")";

    return os;
}

// 命名空间的扩展
namespace std {

// 模板的特化
template <> struct hash<Point> {
    size_t operator( )(const Point &rhs) const {
        cout << "template <>" << endl;
        return ((rhs.getX( ) << 1) ^ (rhs.getY( ) << 2));
    }

}; // end of name hash

} // end of namespace std

// bool operator==(const Point &lhs, const Point &rhs) {
// cout << "bool operator==" << endl;
// return ((lhs.getX() == rhs.getX()) && (lhs.getY() == rhs.getY()));
// }

void test( ) {
    std::unordered_multimap<int, Point> number = {{1, Point(1, 2)}, {1, {1, 2}}};
    auto it =number.begin();
    --it;
    // {1,Point(1, 2)}, Point(-1, 2), Point(1, 2), Point(3, 2), Point(1, 10), Point(1, -2),
    // };
    display(number);
}

int main(int argc, char *argv[]) {
    test( );
    return 0;
}
