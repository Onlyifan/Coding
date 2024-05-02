#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

int globalA = 1;

// typedef void (*pFunc) (const string &);
// using pFunc = void(const string &);
using pFunc = vector<int> (*)(const string &);

// pFunc it = [](const string &str) -> vector<int> { return {1, 2}; };


class Example {
  public:
    void print(int x, int y) {
        // auto x1 = [] { return _number; };
        auto x2 = [this]( ) {
            this->_number++;
            return _number;
        };
        // auto x3 = [this] { return _number + x + y; };
        auto x4 = [this, x, y] { return _number + x + y; };
        auto x5 = [this] { return _number++; };
        // auto x6 = [=] { return ++_number + x + y; };
        auto x6 = [=] { return ++_number; };
        auto x7 = [&] { return _number + x + y; };
    }

  private:
    int _number = 100;
};

void test( ) {
    string a1;

    [&](const string &str) -> vector<int> { return {1, 2}; }("aa");
    auto x1 = [] { return globalA; };
}


int main(void) {

    int a = 1;
    {
        int b = 2;

        auto x1 = [&a] { return ++a; };
    }

    return 0;
}
