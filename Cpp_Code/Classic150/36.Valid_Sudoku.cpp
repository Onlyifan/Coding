#include <leetcode.h>
using namespace std;


class Solution1 {
  public:
    bool isValidSudoku(vector<vector<char>> &board) {


        for (int i = 0; i != 9; ++i) {
            array<bool, 9> isExist{ };
            for (int j = 0; j != 9; ++j) {
                char ch = board[i][j];
                if (ch == '.') {
                    continue;
                }
                if (isExist[ch - '1'] == true) {
                    return false;
                }
                isExist[ch - '1'] = true;
            }
        }


        for (int i = 0; i != 9; ++i) {
            array<bool, 9> isExist{ };
            for (int j = 0; j != 9; ++j) {
                char ch = board[j][i];
                if (ch == '.') {
                    continue;
                }
                if (isExist[ch - '1'] == true) {
                    return false;
                }
                isExist[ch - '1'] = true;
            }
        }


        for (int i = 0; i != 9; i += 3) {
            for (int j = 0; j != 9; j += 3) {
                array<bool, 9> isExist{ };
                for (int m = 0; m != 3; ++m) {
                    for (int n = 0; n != 3; ++n) {

                        char ch = board[i + m][j + n];
                        if (ch == '.') {
                            continue;
                        }
                        if (isExist[ch - '1'] == true) {
                            return false;
                        }
                        isExist[ch - '1'] = true;
                    }
                }
            }
        }

        return true;
    }
};


class Solution {
  public:
    bool isValidSudoku(vector<vector<char>> &board) {

        array<array<bool, 9>, 9> Rows;
        array<array<bool, 9>, 9> Columns;
        array<array<bool, 9>, 9> Areas;


        for (int i = 0; i != 9; ++i) {
            for (int j = 0; j != 9; ++j) {
                char ch = board[i][j];
                if (ch == '.') {
                    continue;
                }
                int index = ch - '1';
                if (Rows[i][index] == true || Columns[j][index] == true ||
                    Areas[i / 3 * 3 + j / 3][index] == true) {
                    return false;
                }

                Rows[i][index] = true;
                Columns[j][index] = true;
                Areas[i / 3 * 3 + j / 3][index] = true;
            }
        }

        return true;
    }
};
