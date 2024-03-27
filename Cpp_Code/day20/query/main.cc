#include "query_result.hh"
#include "text_query.hh"
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;


int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "ERROR: Args not match." << endl;
        return 1;
    }

    ifstream ifs(argv[1]);

    if (!ifs.is_open( )) {
        cerr << "ERROR: File not exist." << endl;
        return 2;
    }


    string word;
    for (;;) {
        std::cin >> word;
        if (std::cin.eof( )) {
            return 0;
        }


        cout << TextQuery::getInstance(ifs).query(word) << endl;
    }

    return 0;
}
