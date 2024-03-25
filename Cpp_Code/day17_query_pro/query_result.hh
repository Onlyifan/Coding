#ifndef _QUERY_RESULT_HH_
#define _QUERY_RESULT_HH_


#include <cstddef>
#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <vector>


class QueryResult {
    friend std::ostream &operator<<(std::ostream &, const QueryResult &);

  public:
    QueryResult(std::string soughtWord, std::shared_ptr<std::set<std::size_t>> lines,
                std::shared_ptr<std::vector<std::string>> fileByLine)
        : _soughtWord(soughtWord)
        , _lines(lines)
        , _fileByLine(fileByLine) {}

    std::set<std::size_t>::iterator begin( ) {
        return _lines->begin( );
    }

    std::set<std::size_t>::iterator end( ) {
        return _lines->end( );
    }

    std::size_t size( ) {
        return _fileByLine->size( );
    }

    std::shared_ptr<std::vector<std::string>> getFile( ) {
        return _fileByLine;
    }


  private:
    std::string _soughtWord;
    std::shared_ptr<std::set<std::size_t>> _lines;
    std::shared_ptr<std::vector<std::string>> _fileByLine;
};


#endif // _QUERY_RESULT_HH_
