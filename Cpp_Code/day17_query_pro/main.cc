#include "parse_input.hh"
#include "query.hh"
#include "query_result.hh"
#include "text_query.hh"

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::unique_ptr;


int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "ERROR: Args not match." << endl;
        return 1;
    }

    unique_ptr<ifstream> pIfs(new ifstream(argv[1]));

    if (!pIfs->is_open( )) {
        cerr << "ERROR: File not exist." << endl;
        cerr << "ERROR: File not exist." << endl;
        return 2;
    }

    TextQuery map(std::move(pIfs));
    string line;
    for (;;) {
        std::getline(std::cin, line);
        if (std::cin.eof( )) {
            return 0;
        }

        cout << parseInput(line).eval(map) << endl;
    }

    return 0;
}
