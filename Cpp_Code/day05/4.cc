#include <iostream>
using std::cout;
using std::endl;

const int STACK_CAPACITY_DEFAULT = 5;

class Stack {
  public:
    Stack(int size = STACK_CAPACITY_DEFAULT)
        : _top(-1)
        , _capacity(size <= 0 ? STACK_CAPACITY_DEFAULT : size)
        , _pstack(new int[size <= 0 ? STACK_CAPACITY_DEFAULT : size]( )) {}

    ~Stack( ) {
        if (_pstack) {
            delete[] _pstack;
            _pstack = nullptr;
        }
    }

    Stack(Stack &rhs)
        : _top(rhs._top)
        , _capacity(rhs._capacity)
        , _pstack(new int[rhs._capacity]( )) {
        memcpy(_pstack, rhs._pstack, sizeof(int) * (rhs._top + 1));
    }

    Stack &operator=(Stack &rhs) {
        if (this != &rhs) {
            _top = rhs._top;
            _capacity = rhs._capacity;
            delete[] _pstack;
            _pstack = new int[rhs._capacity]( );
            memcpy(_pstack, rhs._pstack, sizeof(int) * (rhs._top + 1));
        }

        return *this;
    }

    void print( ) {
        for (int i = 0; i <= _top; ++i) {
            cout << _pstack[i] << " ";
        }
        cout << "bottom" << endl;
    }

    bool empty( ) const { return _top == -1; }
    bool full( ) const { return _top + 1 == _capacity; }
    void push(int data) {
        if (full( ) == false) {
            _pstack[++_top] = data;
        }
    }
    void pop( ) {
        if (empty( ) == false) {
            --_top;
        }
    }
    int top( ) const {
        if (empty( ) == true) {
            throw "Error: stack was empty!";
        }
        return _pstack[_top];
    }

  private:
    int _top;
    int _capacity;
    int *_pstack;
};

int main(void) {
    Stack s1;
    s1.pop( );
    s1.print( );
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);
    s1.print( );
    s1.push(5);
    s1.print( );
    s1.push(6);
    s1.print( );
    s1.pop( );
    s1.pop( );
    s1.pop( );

    int data;
    try {
        data = s1.top( );
    } catch (const char *str) {
        cout << str << endl;
    }

    cout << "top data is " << data << endl;

    s1.pop( );
    s1.pop( );
    s1.pop( );
    s1.pop( );

    try {
        data = s1.top( );
    } catch (const char *str) {
        cout << str << endl;
    }

    cout << data << endl;
    return 0;
}
