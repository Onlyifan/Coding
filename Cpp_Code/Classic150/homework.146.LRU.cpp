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


class LRUCache {
  public:
    LRUCache(size_t capacity)
        : _capacity(capacity) {
        _hash.reserve(capacity << 1);
    }

    int get(int key) {
        auto it = _hash.find(key);
        if (it == _hash.end( )) {
            return -1;
        }

        _list.splice(_list.end( ), _list, it->second.second);

        return it->second.first;
    }

    void put(int key, int value) {
        auto it = _hash.find(key);
        if (it != _hash.end( )) {
            it->second.first = value;
            _list.splice(_list.end( ), _list, it->second.second);
            return;
        }

        _list.emplace_back(key);
        _hash.emplace(key, make_pair(value, --_list.end( )));

        if (_list.size( ) > _capacity) {
            _hash.erase(_list.front( ));
            _list.pop_front( );
        }
    }

  private:
    unordered_map<int, pair<int, list<int>::iterator>> _hash;
    list<int> _list;
    size_t _capacity;
};


/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
