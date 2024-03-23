#include "test.hpp"

#include <iostream>

using std::cout;
using std::endl;

int func1(void) {
  myClass qq;
  qq.print();

  return 0;
}

extern int func2();

int main(int argc, char *argv[]) {
  func1();
  func2();

  return 0;
}
