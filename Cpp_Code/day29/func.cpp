#include <algorithm>
#include <array>
#include <bitset>
#include <chrono>
#include <cmath>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <thread>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>
using namespace std;


class oFunc {
  public:
    void operator( )(int x) {
        cout << x << endl;
        return;
    }
};

class fffFunc {
  public:
    void fff(int x) {
        cout << x << endl;
        return;
    }
};

void hh(int x) {
    cout << x << endl;
    return;
}


void jj(int x, int y) {
    cout << x << endl;
    cout << "hellocqexwb" << endl;
    return;
}


void test( ) {
    // typedef void (*pFunc)(int);
    // using pFunc = void (*)(int);

    // typedef void (&ppFunc)(int);
    // using ppFunc = void (&)(int);

    // pFunc p1 = hh;
    // ppFunc p2 = hh;

    // auto a1 = bind(p1, 1);
    // auto a1 = bind(hh, 1);
    // auto a1 = bind(&hh, 1);

    // function<void( )> function = a1;

    // thread th1(p1, 1);
    // thread th2(p2, 1);

    oFunc p3;
    // p3(1);
    // oFunc *po = &p3;
    // (*po)(3);

    thread thth1(p3, 1);
    // thread thth2(&p3, 1);
    thth1.join( );
    // thth2.join( );

    // auto a1 = bind(po, 1);
    // auto a1 = bind(p3, 1);
    // fffFunc ff;
    // thread thth1(fffFunc::fff, &ff, 1);
    // thread thth2(&fffFunc::fff, &ff, 1);
    // thth1.join( );
    // thth2.join( );
    // auto a1 = bind(&jj, 1, 2);
    // auto a1 = bind(&hh, 1);

    // function<void( )> function = a1;
    // thread th3(p3, 1);
    // thread th4(&p3, 1);
}

int main( ) {
    test( );
}
