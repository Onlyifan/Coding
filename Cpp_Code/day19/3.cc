#include <cstddef>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::size_t;
using std::vector;


template <typename T, typename Compare = std::less<T>> class HeapSort {
  public:
    HeapSort(T *arr, size_t size);
    void heapAdjust(size_t, size_t);
    void sort( );
    void print( );

  private:
    vector<T> _vec;
    Compare _cmp;
};

template <typename T, typename Compare>
HeapSort<T, Compare>::HeapSort(T *arr, size_t size)
    : _vec(arr, arr + size) {}
// , _cmp(Compare( )) {}


template <typename T, typename Compare> void HeapSort<T, Compare>::print( ) {
    for (auto &elem : _vec) {
        cout << elem << " ";
    }
    cout << endl;
}


template <typename T, typename Compare>
void HeapSort<T, Compare>::heapAdjust(size_t start, size_t end) {
    size_t range = (end - start) / 2;
    if (0 == (end - start) % 2) {
        --range;
        if (_cmp(_vec[range], _vec[end - 1])) {
            std::swap(_vec[range], _vec[end - 1]);
        }
    }

    for (size_t i = range - 1; i >= 0; --i) {
        if (_cmp(_vec[i], _vec[2 * i + 1])) {
            std::swap(_vec[i], _vec[2 * i + 1]);
        }

        if (_cmp(_vec[i], _vec[2 * i + 2])) {
            std::swap(_vec[i], _vec[2 * i + 2]);
        }
    }
}


template <typename T, typename Compare> void HeapSort<T, Compare>::sort( ) {
    for (size_t i = _vec.size( ); i != 0; --i) {
        heapAdjust(0, i);
        std::swap(_vec.front( ), _vec[i - 1]);
    }
}

int main(void) {

    int arr[]{3, 1, 4, 6, 8, 3, 5, 7, 5};
    HeapSort hsort(arr, sizeof(arr) / sizeof(arr[0]));
    hsort.print( );
    hsort.sort( );

    hsort.print( );


    return 0;
}
