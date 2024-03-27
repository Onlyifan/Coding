#include "query_result.hh"
#include "string_highlight.hh"
#include <ostream>

using std::endl;
using std::size_t;

std::ostream &operator<<(std::ostream &os, const QueryResult &qr) {
    os << "---------------------------------------------" << endl;
    os << render::highlightSubStr(qr._soughtWord, qr._soughtWord) << " occurs " << qr._lines->first
       << " time" << (qr._lines->first > 1 ? "s" : "") << endl;
    for (auto &lineNum : qr._lines->second) {
        os << "(line " << lineNum + 1 << ") "
           << render::highlightSubStr((*qr._fileByLine)[lineNum], qr._soughtWord) << endl;
    }
    return os << "---------------------------------------------" << endl << endl;
}
