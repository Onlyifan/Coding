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


class Solution {
  public:
    int candy(vector<int> &ratings) {
        int size = ratings.size( ) - 1;

        if (2 > size) {
            return size + 1 + (ratings.front( ) != ratings.back( ));
        }

        for (int i = 0; i != size; ++i) {
            ratings[i] = ratings[i + 1] - ratings[i];
        }

        int sum = 0;

        int i = 0;
        while (i != size) {
            int positive = 0;
            int negative = 0;
            if (ratings[i] < 0) {
                while (i != size && ratings[i] < 0) {
                    ++negative;
                    ++i;
                }
                sum += calcu(negative, 0);
            } else if (ratings[i] > 0) {
                while (i != size && ratings[i] > 0) {
                    ++positive;
                    ++i;
                }

                while (i != size && ratings[i] < 0) {
                    ++negative;
                    ++i;
                }

                sum += calcu(negative, positive);
            } else {
                ++i;
            }
        }


        return size + 1 + sum;
    }
    static int calcu(int a, int b) {
        if (a > b) {
            return a * (a + 1) / 2 + b * (b - 1) / 2;
        } else {
            return b * (b + 1) / 2 + a * (a - 1) / 2;
        }
    }
};


class Solution1 {
  public:
    int candy(vector<int> &ratings) {
        int size = ratings.size( ) - 1;

        int sum = 0;

        int i = 0;
        while (i != size) {
            int tmp = ratings[i + 1] - ratings[i];
            ++i;
            if (tmp < 0) {
                int negative = 1;
                while (i != size && ratings[i + 1] - ratings[i] < 0) {
                    ++negative;
                    ++i;
                }
                sum += negative * (negative + 1) >> 1;
            } else if (tmp > 0) {
                int positive = 1;
                int negative = 0;
                while (i != size && ratings[i + 1] - ratings[i] > 0) {
                    ++positive;
                    ++i;
                }
                while (i != size && ratings[i + 1] - ratings[i] < 0) {
                    ++negative;
                    ++i;
                }
                sum += positive * (positive + 1) >> 1;
                sum += negative * (negative + 1) >> 1;
                sum -= min(positive, negative);
            }
        }

        return size + 1 + sum;
    }
};


class Solution {
  public:
    int candy(vector<int> &ratings) {
        int size = ratings.size( ) - 1;

        int sum = 0;

        int i = 0;
        while (i != size) {
            if (ratings[i + 1] == ratings[i]) {
                ++i;
                continue;
            }

            int positive = 0;
            int negative = 0;
            while (i != size && ratings[i + 1] > ratings[i]) {
                sum += ++positive;
                ++i;
            }

            while (i != size && ratings[i + 1] < ratings[i]) {
                sum += ++negative;
                ++i;
            }
            sum -= min(positive, negative);
        }

        return sum + size + 1;
    }
};


// final solution

class Solutionf {
  public:
    int candy(vector<int> &ratings) {

        int sum = 0;
        int i = 1;

        while (i != ratings.size( )) {
            while (i != ratings.size( ) && ratings[i] == ratings[i - 1]) {
                ++i;
            }

            int positive = 0;
            int negative = 0;
            while (i != ratings.size( ) && ratings[i] > ratings[i - 1]) {
                ++positive;
                ++i;
            }

            while (i != ratings.size( ) && ratings[i] < ratings[i - 1]) {
                ++negative;
                ++i;
            }

            if (negative < positive) {
                swap(negative, positive);
            }

            sum += negative * (negative - 1);

            sum += (positive - negative + 1) * (positive + negative) / 2;
        }

        return sum + ratings.size( );
    }
};
