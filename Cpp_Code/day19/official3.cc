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
    : _vec(arr, arr + size)
    , _cmp( ) {}


template <typename T, typename Compare> void HeapSort<T, Compare>::print( ) {
    for (auto &elem : _vec) {
        cout << elem << " ";
    }
    cout << endl;
}


template <typename T, typename Compare>
void HeapSort<T, Compare>::heapAdjust(size_t start, size_t end) {
    size_t parent = start;

    for (;;) {
        size_t largestIndex = parent;
        size_t left = 2 * parent + 1;
        size_t right = 2 * parent + 2;


        if ((left < end) && _cmp(_vec[largestIndex], _vec[left])) {
            largestIndex = left;
        }

        if ((right < end) && _cmp(_vec[largestIndex], _vec[right])) {
            largestIndex = right;
        }

        if (parent != largestIndex) {
            std::swap(_vec[parent], _vec[largestIndex]);
            parent = largestIndex;
        } else {
            return;
        }
    }
}

template <typename T, typename Compare> void HeapSort<T, Compare>::sort( ) {
    for (int i = _vec.size( ) / 2 - 1; i >= 0; --i) {
        heapAdjust(i, _vec.size( ));
        cout << "a sort" << endl;
    }

    for (int i = _vec.size( ) - 1; i > 0; --i) {
        std::swap(_vec[0], _vec[i]);
        heapAdjust(0, i);
    }
}

int main(void) {

    // int arr[]{3, 1, 4, 6, 8, 7, 5};
    int arr[] = {12, 11, 13, 5, 6, 7};
    HeapSort<int> hsort(arr, sizeof(arr) / sizeof(arr[0]));
    hsort.print( );
    hsort.sort( );

    hsort.print( );


    return 0;
}
