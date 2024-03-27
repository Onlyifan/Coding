#include "text_query.hh"
#include "query_result.hh"
#include <iostream>
#include <sstream>

using namespace std;

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


TextQuery::TextQuery(ifstream &ifs)
    : _dict( )
    , _file(make_shared<vector<string>>( )) {
    string line;
    string word;

    while (getline(ifs, line)) {
        _file->push_back(line);
        handlerLine(line);
        istringstream iss(line);

        while (iss >> word) {
            auto &ret = _dict[word];
            // if (ret == nullptr) {
            if (ret.get( ) == nullptr) {
            // if (!ret) {
                ret = make_shared<pair<size_t, set<size_t>>>( );
                // ret.reset(new pair<size_t, set<size_t>>( ));
            }
            ++ret->first;
            ret->second.insert(_file->size( ) - 1);
        }
    }
    cout << _dict.begin( )->second->first << endl;
}
TextQuery *TextQuery::_pInstance = nullptr;

TextQuery &TextQuery::getInstance(ifstream &ifs) {
    if (_pInstance == nullptr) {
        _pInstance = new TextQuery(ifs);
    }
    return *_pInstance;
}


QueryResult TextQuery::query(const string &str) const {
    string loweredStr(str);
    std::transform(loweredStr.begin( ), loweredStr.end( ), loweredStr.begin( ), ::tolower);

    auto it = _dict.find(loweredStr);
    if (it == _dict.end( )) {
        static shared_ptr<pair<size_t, set<size_t>>> noLine =
            make_shared<pair<size_t, set<size_t>>>( );
        return QueryResult(str, noLine, _file);
    }

    return QueryResult(str, it->second, _file);
}
