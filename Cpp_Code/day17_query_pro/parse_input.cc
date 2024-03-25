#include "parse_input.hh"
#include <stack>
#include <vector>

using std::string;

Query parseInput(const string &str) {
    string word;
    std::stack<char> opStack;
    std::vector<Query> queryStack;

    std::size_t i = 0;
    while (i != str.size( )) {
        switch (str[i]) {
        case '~':
        case '&':
            opStack.push(str[i]);
            while ('&' == str[i + 1]) {
                ++i;
            }
            break;
        case ' ':
        case '|':
            break;
        default:
            word.clear( );
            for (;;) {
                word.push_back(str[i]);

                if (i + 1 == str.size( )) {
                    break;
                }
                if (str[i + 1] != '~' && str[i + 1] != '|' && str[i + 1] != '&' &&
                    str[i + 1] != ' ') {
                    ++i;
                    continue;
                } else {
                    break;
                }
            }

            Query once(word);

            while (!opStack.empty( )) {
                if (opStack.top( ) == '~') {
                    once = ~once;
                } else if (!queryStack.empty( )) {
                    once = once & queryStack.back( );
                    queryStack.pop_back( );
                }
                opStack.pop( );
            }
            queryStack.push_back(once);
        }

        ++i;
    }


    Query result = queryStack.empty( ) ? Query("") : queryStack.front( );

    for (std::size_t i = 1; i < queryStack.size( ); ++i) {
        result = result | queryStack[i];
    }

    return result;
}
