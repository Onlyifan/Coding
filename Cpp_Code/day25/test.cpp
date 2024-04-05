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
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>
using namespace std;


class ProductA;
class ProductB;
class ConcreteProductA1;
class ConcreteProductB1;

// 抽象工厂接口
class AbstractFactory {
  public:
    virtual ~AbstractFactory( ) {}
    virtual ProductA *createProductA( ) = 0;
    virtual ProductB *createProductB( ) = 0;
};

// 具体工厂类
class ConcreteFactory1 : public AbstractFactory {
  public:
    ProductA *createProductA( ) override { return nullptr; }

    ProductB *createProductB( ) override { return nullptr; }
};
