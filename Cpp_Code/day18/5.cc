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


template <typename T, typename Compare = std::less<T>> class MyQsort {

  public:
    MyQsort(T *arr, size_t size, Compare = Compare( ));
    void quick(int left, int right, Compare &com);
    int partition(int left, int right, Compare &com);

    void print( );

  private:
    vector<T> _vec;
};

template <typename T, typename Compare>
MyQsort<T, Compare>::MyQsort(T *arr, size_t size, Compare com)
    : _vec(vector<T>(arr, arr + size)) {
    quick(0, size - 1, com);
}

template <typename T, typename Compare>
void MyQsort<T, Compare>::quick(int left, int right, Compare &com) {
    if (left >= right) {
        return;
    }

    int index = partition(left, right, com);

    quick(left, index - 1, com);
    quick(index + 1, right, com);
}

template <typename T, typename Compare>
int MyQsort<T, Compare>::partition(int left, int right, Compare &com) {
    T pivot = _vec[left];


    for (;;) {
        while (left < right && com(_vec[left], pivot)) {
            ++left;
        }

        while (left < right && com(pivot, _vec[right])) {
            --right;
        }

        if (left >= right) {
            return left;
        }

        std::swap(_vec[left], _vec[right]);
        ++left;
        --right;
    }
}

template <typename T, typename Compare> void MyQsort<T, Compare>::print( ) {
    for (T &elem : _vec) {
        cout << elem << " ";
    }
    cout << endl;
}


int main(void) {

    int arr[]{3, 2, 4, 5, 1};
    MyQsort<int> qvec(arr, sizeof(arr) / sizeof(arr[0]));
    qvec.print( );


    return 0;
}
