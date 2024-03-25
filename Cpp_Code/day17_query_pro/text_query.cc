#include "text_query.hh"
#include "query_result.hh"
#include <fstream>
#include <sstream>

using std::ifstream;
using std::istringstream;
using std::set;
using std::shared_ptr;
using std::string;
using std::unique_ptr;
using std::vector;

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

TextQuery::TextQuery(unique_ptr<ifstream> &&pIfs)
    : _fileByLine(new vector<string>) {

    int lineNumber = -1;
    string word;
    string line;
    while (std::getline(*pIfs, line)) {
        ++lineNumber;
        _fileByLine->push_back(line);

        handlerLine(line);
        istringstream iss(line);
        while (iss >> word) {
            auto &ptr = _dict[word];
            if (!ptr) {
                ptr.reset(new set<size_t>);
            }
            ptr->insert(lineNumber);
        }
    }
}


QueryResult TextQuery::query(const string &str) const {
    string loweredStr(str);
    std::transform(loweredStr.begin( ), loweredStr.end( ), loweredStr.begin( ), ::tolower);

    auto it = _dict.find(loweredStr);
    if (it == _dict.end( )) {
        static shared_ptr<set<size_t>> noLine(new set<size_t>);
        return QueryResult(str, noLine, _fileByLine);
    }
    return QueryResult(str, it->second, _fileByLine);
}
