#include <iostream>
#include <memory>
#include <string>
using std::cout;
using std::endl;
using std::string;

template <typename T> class Vector {
    using iterator = T *;

  public:
    Vector( )
        : _start(nullptr)
        , _finish(nullptr)
        , _end_of_storage(nullptr) {}
    ~Vector( );

    void push_back(const T &);
    void pop_back( );

    int size( ) const { return _finish - _start; }
    int capacity( ) const { return _end_of_storage - _start; }
    iterator begin( ) { return _start; }
    iterator end( ) { return _finish; }


  private:
    void reallocate( ); // 重新分配内存,动态扩容要用的
  private:
    static std::allocator<T> _alloc;
    T *_start;          // 指向数组中的第一个元素
    T *_finish;         // 指向最后一个实际元素之后的那个元素
    T *_end_of_storage; // 指向数组本身之后的位置
};
template <typename T> std::allocator<T> Vector<T>::_alloc;

template <typename T> Vector<T>::~Vector( ) {
    while (_start != _finish) {
        _alloc.destroy(--_finish);
    }
    _alloc.deallocate(_start, capacity( ));
}

// template <typename T> Vector<T>::
template <typename T> void Vector<T>::push_back(const T &elem) {
    if (size( ) == capacity( )) {
        reallocate( );
    }

    _alloc.construct(_finish++, elem);
}


template <typename T> void Vector<T>::pop_back( ) {
    if (size( )) {
        _alloc.destroy(--_finish);
    }
}

template <typename T> void Vector<T>::reallocate( ) {
    if (_start == nullptr) {
        _start = _finish = _end_of_storage = _alloc.allocate(1);
        _end_of_storage += 1;
        return;
    }

    size_t oldCapacity = capacity( );
    size_t newCapacity = oldCapacity << 1;
    T *tmp = _alloc.allocate(newCapacity);
    std::uninitialized_copy(_start, _finish, tmp);
    while (_start != _finish) {
        _alloc.destroy(--_finish);
    }
    _alloc.deallocate(_start, oldCapacity);

    _start = tmp;
    _finish = tmp + oldCapacity;
    _end_of_storage = tmp + newCapacity;
}


void printCapacity(const Vector<int> &con) {
    cout << "size() = " << con.size( ) << endl;
    cout << "capacity() = " << con.capacity( ) << endl;
}


void test( ) {
    Vector<int> vec;
    printCapacity(vec);

    cout << endl;
    vec.push_back(1);
    printCapacity(vec);

    cout << endl;
    vec.push_back(2);
    printCapacity(vec);

    cout << endl;
    vec.push_back(3);
    printCapacity(vec);

    cout << endl;
    vec.push_back(4);
    printCapacity(vec);

    cout << endl;
    vec.push_back(5);
    printCapacity(vec);

    for (auto &elem : vec) {
        cout << elem << "  ";
    }
    cout << endl;
}
int main( ) {
    test( );
    return 0;
}
