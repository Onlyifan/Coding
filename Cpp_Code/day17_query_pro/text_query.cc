#include "text_query.hh"
#include "string_highlight.hh"
#include <fstream>
#include <iostream>
#include <sstream>

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::map;
using std::set;
using std::shared_ptr;
using std::string;
using std::unique_ptr;
using std::vector;

void IFSCloser::operator( )(ifstream *pIfs) {
    pIfs->close( );
    cout << "finish void IFSCloser::operator( )(ifstream *pIfs)" << endl;
}

void handlerLine(string &line) {
    if (line[0] == '\'') {
        line[0] = ' ';
    }
    if (*line.end( ) == '\'') {
        *line.end( ) = ' ';
    }
    for (char &ch : line) {
        if (isalnum(ch)) {
            ch = tolower(ch);
            continue;
        }
        if (ch == '\'' && isalpha(*(&ch - 1)) && isalpha(*(&ch + 1))) {
            continue;
        }
        ch = ' ';
    }
}

TextQuery::TextQuery(const string &filename)
    : _lines(new vector<string>) {
    unique_ptr<ifstream, IFSCloser> pIfs(new ifstream(filename));
    if (!*pIfs) {
        cerr << "ERROR: Open file:" << filename << " failed." << endl;
        exit(1);
    }

    int lineNumber = 0;
    char ch;
    string word;
    string line;
    while (std::getline(*pIfs, line)) {
        ++lineNumber;
        _lines->push_back(line);

        handlerLine(line);
        std::istringstream iss(line);
        while (iss >> word) {

            std::pair<int, set<int>> &dict = _dict[word];

            ++dict.first;
            dict.second.insert(lineNumber);
        }
    }
}


QueryResult TextQuery::query(const string &str) const {

    string loweredStr(str);
    std::transform(loweredStr.begin( ), loweredStr.end( ), loweredStr.begin( ),
                   ::tolower);

    // map<string, std::pair<int, set<int>>>::const_iterator it =
    auto it = _dict.find(loweredStr);
    cout << "---------------------------------------------" << endl;
    if (it == _dict.end( )) {
        cout << render::highlightSubStr(str, str) << " was not found in File."
             << endl;
    } else {
        cout << render::highlightSubStr(str, str) << " occurs "
             << it->second.first << " times." << endl;
        for (int const &lineNum : it->second.second) {
            cout << "(line " << lineNum << ") "
                 << render::highlightSubStr((_lines)[lineNum - 1], str) << endl;
        }
    }
    cout << "---------------------------------------------" << endl;
}


bool isFileExist(const string &filename) {
    unique_ptr<ifstream, IFSCloser> pIfs(new ifstream(filename));
    return pIfs->is_open( );
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "ERROR: Args not match." << endl;
        return 1;
    }

    if (!isFileExist(argv[1])) {
        cerr << "ERROR: File not exist." << endl;
        return 2;
    }

    TextQuery map;
    map.readFile(argv[1]);

    while (1) {
        string str;
        std::cin >> str;

        if (std::cin.eof( )) {
            return 0;
        }

        map.query(str);
    }

    return 0;
}
