#ifndef _TEXT_QUERY_HH_
#define _TEXT_QUERY_HH_


#include <cstddef>
#include <fstream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>


class QueryResult;

class TextQuery {
  public:
    TextQuery(std::unique_ptr<std::ifstream> &&pIfs);

    QueryResult query(const std::string &str) const;

    std::set<std::size_t> getLines(const std::string &str);


  private:
    std::shared_ptr<std::vector<std::string>>                _fileByLine;
    std::map<std::string, std::shared_ptr<std::set<size_t>>> _dict;
};


#endif // _TEXT_QUERY_HH_
