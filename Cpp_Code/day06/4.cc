#include <iostream>
#include <limits>
using std::cin;
using std::cout;
using std::endl;


int inputNum( ) {
    cout << "please Input" << endl;
    int num;
    // while ((cin >> num).operator bool( ), !cin.eof( )) {
    while (cin >> num, !cin.eof( )) {

        if (cin.bad( )) {
            cout << "cin was broken" << endl;
            return -1;

            // 当流失效时
        } else if (cin.fail( )) {
            // 调用cin.clear(), 重设错误标志, 让流的状态变为goodbit
            cin.clear( );
            // 然后丢弃缓冲区中从当前位置直到换行符在内的数据以清空输入流
            cin.ignore(std::numeric_limits<std::streamsize>::max( ), '\n');
            cout << "please Input" << endl;
        } else {
            cout << "num is " << num << endl;
            break;
        }
    }

    return 0;
}


int main(void) {

    inputNum( );

    return 0;
}
