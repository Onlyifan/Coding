#include <iostream>
using std::cout;
using std::endl;


class Base {
  public:
    Base(int value)
        : _value(value) {}

    friend Base operator+(const Base &lhs, const Base &rhs);

    friend bool operator==(const Base &lhs, int rhs);

  private:
    int _value;
};

Base operator+(const Base &lhs, const Base &rhs) {

    return Base(lhs._value + rhs._value);
}

bool operator==(const Base &lhs, int rhs) {
    return lhs._value == rhs;
}

int main(void) {
    int i = 2;
    int j = 7;

    Base x(i);
    Base y(j);
    cout << (x + y == j - i) << endl;

    return 0;
}
