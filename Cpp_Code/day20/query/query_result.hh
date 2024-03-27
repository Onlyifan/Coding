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
    QueryResult(std::string soughtWord,
                std::shared_ptr<std::pair<std::size_t, std::set<std::size_t>>> lines,
                std::shared_ptr<std::vector<std::string>> fileByLine)
        : _soughtWord(soughtWord)
        , _lines(lines)
        , _fileByLine(fileByLine) {}

  private:
    std::string _soughtWord;
    std::shared_ptr<std::pair<std::size_t, std::set<std::size_t>>> _lines;
    std::shared_ptr<std::vector<std::string>> _fileByLine;
};


#endif // _QUERY_RESULT_HH_
