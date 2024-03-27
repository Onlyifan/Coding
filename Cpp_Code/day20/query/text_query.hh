#ifndef _WORDQUERY_HH_
#define _WORDQUERY_HH_


#include <cstddef>
#include <fstream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <utility>


class QueryResult;
class TextQuery {
    TextQuery(const TextQuery &) = delete;
    TextQuery &operator=(const TextQuery &) = delete;

  public:
    static TextQuery &getInstance(std::ifstream &ifs);

    QueryResult query(const std::string &str) const;


  private:
    TextQuery(std::ifstream &);
    ~TextQuery( ) = default;

    std::map<std::string, std::shared_ptr<std::pair<std::size_t, std::set<std::size_t>>>> _dict;
    std::shared_ptr<std::vector<std::string>> _file;
    static TextQuery *_pInstance;
};


#endif // _WORDQUERY_HH_
