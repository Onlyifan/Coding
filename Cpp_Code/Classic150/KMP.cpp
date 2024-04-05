#include <algorithm>
#include <array>
#include <bitset>
#include <chrono>
#include <cmath>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>
using namespace std;


vector<size_t> generateNext(string &str) {
    vector<size_t> nextArr(str.size( )); // nextArr[0] == 0;

    int i = 1;
    int prefixLen = 0;
    while (i != str.size( )) {
        if (str[i] == str[prefixLen]) {
            ++prefixLen;
            nextArr[i] = prefixLen;
        } else {
            if (0 == prefixLen) {
                nextArr[i++] = 0;
            } else {
                prefixLen = nextArr[prefixLen - 1];
            }
        }
    }
    return nextArr;
}

size_t getSubstrIndex(string &main, string &sub) {
    vector<size_t> nextArr = generateNext(sub);

    int i = 0;
    int prefixLen = 0;
    while (i != main.size( )) {
        if (main[i] == sub[prefixLen]) {
            ++i;
            ++prefixLen;
        } else {
            if (0 == prefixLen) {
                ++i;
            } else {
                prefixLen = nextArr[prefixLen - 1];
            }
        }

        if (prefixLen == sub.size( )) {
            return i - prefixLen;
        }
    }

    return -1;
}
