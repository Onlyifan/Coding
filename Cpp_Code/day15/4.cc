#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;


template <typename T> class myArray {
  public:
    template <typename... Args>
    myArray(Args &&...elements)
        : _size(sizeof...(elements))
        // , _arr(new T[_size]{(T)elements...}) {}
        // , _arr(new T[_size]{static_cast<T>(elements)...}) {}
        , _arr(new T[_size]{static_cast<T>(elements)...}) {}

    myArray(size_t size)
        : _size(size)
        , _arr(new T[size]( )) {}

    T &operator[](size_t index);

    T &back( );

    template <typename... Args> void display( ) {
        for (int i = 0; i < _size; ++i) {
            cout << _arr[i] << ' ';
        }
        cout << endl;
    }

    ~myArray( ) {
        if (_arr) {
            delete[] _arr;
            _arr = nullptr;
        }
    }

  private:
    size_t _size;
    T *_arr;
};

template <typename T> T &myArray<T>::operator[](size_t index) {
    return _arr[index];
}

template <typename T> T &myArray<T>::back( ) {
    return _arr[_size - 1];
}


int main(void) {
    myArray<char> arr1('a', 'b', 'c');
    myArray<double> arr2(1.1, 2, 3.3, 4);
    myArray<int> arr3(1.1, 2, 3.3, 4);
    myArray<string> arr4("abc", string("123"));
    arr1.display( );
    arr2.display( );
    arr3.display( );
    arr4.display( );


    return 0;
}
