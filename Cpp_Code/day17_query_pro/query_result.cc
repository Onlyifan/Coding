#include "query_result.hh"
#include "string_highlight.hh"
#include <ostream>

using std::endl;
using std::size_t;

std::ostream &operator<<(std::ostream &os, const QueryResult &qr) {
    os << "---------------------------------------------" << endl;
    os << render::highlightSubStr(qr._soughtWord, qr._soughtWord) << " occurs "
       << qr._lines->size( ) << " time" << (qr._lines->size( ) > 1 ? "s" : "") << endl;
    for (const size_t &lineNum : *(qr._lines)) {
        os << "(line " << lineNum + 1 << ") "
           << render::highlightSubStr((*qr._fileByLine)[lineNum], qr._soughtWord) << endl;
    }
    os << "---------------------------------------------" << endl << endl;
    return os;
}
