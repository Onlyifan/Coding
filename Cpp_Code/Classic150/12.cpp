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


class RandomizedSet {
  public:
    RandomizedSet( ) {}

    bool insert(int val) {
        bool result = _hashTable.emplace(val, _indexToVal.size( )).second;
        if (result == true) {
            _indexToVal.emplace_back(val);
        }

        return result;
    }

    bool remove(int val) {
        auto it = _hashTable.find(val);
        if (it == _hashTable.end( )) {
            return false;
        }

        _indexToVal[it->second] = _indexToVal.back( );
        _hashTable[_indexToVal.back( )] = it->second;

        _indexToVal.pop_back( );
        _hashTable.erase(it);

        return true;
    }

    int getRandom( ) {
        return _indexToVal[rand( ) % _indexToVal.size( )];
    }

  private:
    unordered_map<int, int> _hashTable;
    vector<int> _indexToVal;
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
