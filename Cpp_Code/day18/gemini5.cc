#include <cstddef>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::size_t;
using std::string;
using std::vector;

template <typename T, typename Compare = std::less<T>>
class MyQsort {
public:
  friend std::ostream& operator<<(std::ostream& os, const MyQsort<T, Compare>& myQ);

  MyQsort(T* arr, size_t size, Compare com);
  void quick(int left, int right, Compare& com);
  int partition(int left, int right, Compare& com);

private:
  vector<T> _vec;
};

// 将 operator<< 声明为 friend 函数
template <typename T, typename Compare>
std::ostream& operator<<(std::ostream& os, const MyQsort<T, Compare>& myQ) {
  for (const auto& elem : myQ._vec) {
    os << elem << " ";
  }
  return os;
}

template <typename T, typename Compare>
MyQsort<T, Compare>::MyQsort(T* arr, size_t size, Compare com)
  : _vec(vector<T>(arr, arr + size)) {
  quick(0, size - 1, com);
}

// ... 其余代码保持相同 ...

int main(void) {
  int arr[] = {3, 2, 4, 5, 1};
  MyQsort<int> qvec(arr, sizeof(arr) / sizeof(arr[0]), std::less<int>{});
  cout << qvec << endl;

  return 0;
}

