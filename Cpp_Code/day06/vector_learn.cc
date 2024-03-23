#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

void showVectorInfo(vector<int> &nums) {
    cout << "vector's size = " << nums.size( ) << endl;
    cout << "vector's capacity = " << nums.capacity( ) << endl;
    cout << "vector's elements: " << endl;


    for (int i = 0; i < nums.size( ); ++i) {
        cout << nums[i] << " ";
    }
    cout << endl;

    for (vector<int>::iterator it = nums.begin( ); it < nums.end( ); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    for (const auto &num : nums) {
        cout << num << " ";
    }
    cout << endl;
    cout << endl;
}

int main(void) {
    // vector<int> v1;
    // showVectorInfo(v1);
    // clang编译器扩容策略为翻倍
    // for(int i = 0; i < 9; ++i) {
    //     v1.push_back(i);
    //     showVectorInfo(v1);
    // }
    //
    // 创建空对象
    // vector<int> v1;
    // showVectorInfo(v1);
    // 这样写实际上是声明一个返回值类型为vector<int> 的函数
    // vector<int> v2(); // ERROR
    // vector<int> v2 = vector<int>( );
    // showVectorInfo(v2);
    // vector<int> v3{ };
    // showVectorInfo(v3);
    // vector<int> *v4 = new vector<int>( );
    //
    //
    //
    // 初始化对象
    int arr0[5] = {1, 2, 3, 4, 5};
    vector<int> v0 = {1, 2, 3, 4, 5};

    // vector<int> v1(10);
    // vector<int> v2(10, 5);
    // vector<int> v1(arr0, arr0 + 3);
    // vector<int> v2(v0.begin(), v0.begin() + 2);
    // vector<int> v1 = v0;
    // showVectorInfo(v1);
    // showVectorInfo(v2);
    //
    // 调用reverse函数
    showVectorInfo(v0);
    v0.reserve(3);
    showVectorInfo(v0);
    //v0.pop_back();
    //v0.pop_back();
    //showVectorInfo(v0);
    //v0.shrink_to_fit();
    //showVectorInfo(v0);
    


    return 0;
}
