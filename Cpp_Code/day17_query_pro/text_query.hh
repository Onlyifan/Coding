#include <fstream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

struct IFSCloser {
    void operator( )(std::ifstream *pIfs);
};

class QueryResult;

class TextQuery {
  public:
    TextQuery(const std::string &filename);

    QueryResult query(const std::string &str) const;

  private:
    std::shared_ptr<std::vector<std::string>> _lines;
    std::map<std::string, std::pair<int, std::set<int>>> _dict;
};
