#include <leetcode.h>
using namespace std;

// 1. 遍历整个数组，统计每个位置的存活状态
class Solution1 {
public:
    void gameOfLife(vector<vector<int>> &board) {
        _firstSize = board.size( );
        _secondSize = board[0].size( );

        for (int i = 0; i != board.size( ); ++i) {
            for (int j = 0; j != board[0].size( ); ++j) {
                char sum = board[i][j];
                if (sum > 0) {
                    sum += updateAlive(board, i, j, 1);

                    if (sum == 3 || sum == 4) {
                        board[i][j] = 1;
                    } else {
                        board[i][j] = 0;
                    }

                } else {
                    sum -= updateAlive(board, i, j, 0);
                    if (sum == -3) {
                        board[i][j] = 1;
                    } else {
                        board[i][j] = 0;
                    }
                }
            }
        }
    }

private:
    int _firstSize;
    int _secondSize;

    bool inArea(int i, int j) {
        return j >= 0 && i < _firstSize && j < _secondSize;
    }

    char updateAlive(vector<vector<int>> &board, int &i, int &j, char alive) {
        char ret = 0;


        if (inArea(i, j + 1)) {
            if (board[i][j + 1] > 0) {
                ++ret;
                board[i][j + 1] += alive;
            } else {
                board[i][j + 1] -= alive;
            }
        }

        if (inArea(i + 1, j - 1)) {
            if (board[i + 1][j - 1] > 0) {
                ++ret;
                board[i + 1][j - 1] += alive;
            } else {
                board[i + 1][j - 1] -= alive;
            }
        }

        if (inArea(i + 1, j)) {
            if (board[i + 1][j] > 0) {
                ++ret;
                board[i + 1][j] += alive;
            } else {
                board[i + 1][j] -= alive;
            }
        }

        if (inArea(i + 1, j + 1)) {
            if (board[i + 1][j + 1] > 0) {
                ++ret;
                board[i + 1][j + 1] += alive;
            } else {
                board[i + 1][j + 1] -= alive;
            }
        }

        return ret;
    }
};

// O4优化版本
class Solution {
public:
    void gameOfLife(vector<vector<int>> &board) {
        for (int i = 0; i != board.size( ); ++i) {
            for (int j = 0; j != board[0].size( ); ++j) {
                char sum = board[i][j];
                if (sum > 0) {
                    sum += updateAlive(board, i, j, 1);

                    if (sum == 3 || sum == 4) {
                    sum1:
                        board[i][j] = 1;
                    } else {
                    sum2:
                        board[i][j] = 0;
                    }

                } else {
                    sum -= updateAlive(board, i, j, 0);
                    if (sum == -3) {
                        goto sum1;
                    } else {
                        goto sum2;
                    }
                }
            }
        }
    }

private:
    static char updateAlive(vector<vector<int>> &board, int i, int j, char alive) {
        char ret = 0;

        if (i + 1 != board.size( )) {
            if (board[i + 1][j] > 0) {
                ++ret;
                board[i + 1][j] += alive;
            } else {
                board[i + 1][j] -= alive;
            }

            if (j != 0) {
                if (board[i + 1][j - 1] > 0) {
                    ++ret;
                    board[i + 1][j - 1] += alive;
                } else {
                    board[i + 1][j - 1] -= alive;
                }
            }

            if (j + 1 != board[0].size( )) {
                if (board[i + 1][j + 1] > 0) {
                    ++ret;
                    board[i + 1][j + 1] += alive;
                } else {
                    board[i + 1][j + 1] -= alive;
                }
                goto last;
            }
        }


        if (j + 1 != board[0].size( )) {
        last:
            if (board[i][j + 1] > 0) {
                ++ret;
                board[i][j + 1] += alive;
            } else {
                board[i][j + 1] -= alive;
            }
        }

        return ret;
    }
};
