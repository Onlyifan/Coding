#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

template <typename T> class Vector {
  public:
    Vector( );
    ~Vector( );
    void push_back(const T &);
    void pop_back( );


    int size( ) { return _finish - _start; }
    int capacity( ) { return _end_of_storage - _start; }
    T &front( ) { return *_start; }
    T &back( ) { return *(_finish - 1); }

  private:
    void reallocate( ); // 重新分配内存,动态扩容要用的
  private:
    static std::allocator<T> _alloc;
    T *_start;          // 指向数组中的第一个元素
    T *_finish;         // 指向最后一个实际元素之后的那个元素
    T *_end_of_storage; // 指向数组本身之后的位置
};


int main(void) {
    return 0;
}
