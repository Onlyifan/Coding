/*
 * @lc app=leetcode.cn id=155 lang=cpp
 * @lcpr version=30122
 *
 * [155] 最小栈
 */


// @lcpr-template-start
#include <leetcode.h>
using namespace std;
// @lcpr-template-end
// @lc code=start

// 辅助map, 不能在O(1)实现要求, 错误解法
class MinStack1 {
public:
    MinStack1( ) {
    }

    void push(int val) {
        auto it = _set.find(val);
        if (it == _set.end( )) {
            _stack.emplace(_set.emplace(val, 1).first);
        } else {
            ++it->second;
            _stack.emplace(it);
        }
    }

    void pop( ) {
        if (_stack.top( )->second == 1) {
            _set.erase(_stack.top( ));
        } else {
            --_stack.top( )->second;
        }
        _stack.pop( );
    }

    int top( ) {
        return _stack.top( )->first;
    }

    int getMin( ) {
        return _set.begin( )->first;
    }

private:
    map<int, int> _set;
    stack<map<int, int>::iterator> _stack;
};


// 辅助栈, pair
class MinStackpair {
public:
    MinStackpair( ) {}

    void push(int val) {
        if (_stack.empty( )) {
            _stack.emplace(val, val);
        } else {
            _stack.emplace(val, min(val, _stack.top( ).second));
        }
    }

    void pop( ) {
        _stack.pop( );
    }

    int top( ) {
        return _stack.top( ).first;
    }

    int getMin( ) {
        return _stack.top( ).second;
    }

private:
    stack<pair<int, int>> _stack;
};


// 辅助栈, 独立的
class MinStack11 {
public:
    MinStack11( ) {}

    void push(int val) {
        _stack.emplace(val);
        if (_stackAux.empty( )) {
            _stackAux.emplace(val);
        } else {
            _stackAux.emplace(min(_stackAux.top( ), val));
        }
    }

    void pop( ) {
        _stack.pop( );
        _stackAux.pop( );
    }

    int top( ) {
        return _stack.top( );
    }

    int getMin( ) {
        return _stackAux.top( );
    }

private:
    stack<int> _stack;
    stack<int> _stackAux;
};


// 不用辅助栈这个额外空间

// 不用辅助栈这个额外空间
class MinStack {
public:
    MinStack( ) {}

    void push(int val) {
        if (_stackDiff.empty( )) {
            _stackDiff.emplace(0);
            _min = val;
        } else {
            _stackDiff.emplace(_min - val);
            if (val < _min) {
                _min = val;
            }
        }
    }

    void pop( ) {
        if (_stackDiff.top( ) > 0) {
            _min += _stackDiff.top( );
        }
        _stackDiff.pop( );
    }

    int top( ) {
        if (_stackDiff.top( ) < 0) {
            return _min - _stackDiff.top( );
        }
        return _min;
    }

    int getMin( ) {
        return _min;
    }

private:
    long long _min;
    stack<long long> _stackDiff;
};

// 不用辅助栈来实现


/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
// @lc code=end


/*
// @lcpr case=start
// ["MinStack","push","push","push","getMin","pop","top","getMin"][[],[-2],[0],[-3],[],[],[],[]]\n
// @lcpr case=end

 */


// 不用辅助栈来实现


/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
// @lc code=end


/*
// @lcpr case=start
// ["MinStack","push","push","push","getMin","pop","top","getMin"][[],[-2],[0],[-3],[],[],[],[]]\n
// @lcpr case=end

 */
