#include <ctype.h>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <utility>

using std::cout;
using std::endl;
using std::map;
using std::set;
using std::string;
using std::vector;

class TextQuery {
  public:
    void handlerLine(string &line);
    void readFile(const string &filename);
    void query(const string &str) const;

  private:
    vector<string> _lines;
    map<string, std::pair<int, set<int>>> _dict;
};


void TextQuery::readFile(const string &filename) {
    std::ifstream ifs(filename);
    if (!ifs) {
        cout << "ERROR: Open file failed." << filename << endl;
        exit(1);
    }

    int lineNumber = 0;
    char ch;
    string word;
    string line;
    while (std::getline(ifs, line)) {
        ++lineNumber;
        _lines.push_back(line);

        handlerLine(line);
        std::istringstream iss(line);
        while (iss >> word) {

            std::pair<int, set<int>> &dict = _dict[word];

            ++dict.first;
            dict.second.insert(lineNumber);
        }
    }

    // istringstream不打开磁盘文件, 离开作用域自动销毁
    ifs.close( );
}

void TextQuery::handlerLine(string &line) {

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

string highlightSubstr(const string &originalStr, const string &targetSubstr) {
    string loweredOriginalStr(originalStr);
    std::transform(loweredOriginalStr.begin( ), loweredOriginalStr.end( ),
                   loweredOriginalStr.begin( ), ::tolower);
    string loweredTargetSubstr(targetSubstr);
    std::transform(loweredTargetSubstr.begin( ), loweredTargetSubstr.end( ),
                   loweredTargetSubstr.begin( ), tolower);

    size_t targetSubstrSize = targetSubstr.size( );
    string highlightedStr;
    size_t currentPos = 0;
    size_t nextPos = 0;

    while ((nextPos = loweredOriginalStr.find(loweredTargetSubstr,
                                              currentPos)) != string::npos) {

        highlightedStr += originalStr.substr(currentPos, nextPos - currentPos);

        if ((nextPos == 0) ||
            !isalnum(originalStr[nextPos - 1]) &&
                ((nextPos + targetSubstrSize == originalStr.size( )) ||
                 !isalnum(originalStr[nextPos + targetSubstrSize]))) {
            highlightedStr += "\033[31m";
            highlightedStr += originalStr.substr(nextPos, targetSubstrSize);
            highlightedStr += "\033[0m";
        } else {
            highlightedStr += originalStr.substr(nextPos, targetSubstrSize);
        }
        currentPos = nextPos + targetSubstrSize;
    }

    highlightedStr += originalStr.substr(currentPos);
    return highlightedStr;
}


void TextQuery::query(const string &str) const {

    string loweredStr(str);
    std::transform(loweredStr.begin( ), loweredStr.end( ), loweredStr.begin( ),
                   ::tolower);

    map<string, std::pair<int, set<int>>>::const_iterator it =
        _dict.find(loweredStr);
    cout << "---------------------------------------------" << endl;
    if (it == _dict.end( )) {
        cout << highlightSubstr(str, str) << " was not found in File." << endl;
    } else {
        cout << highlightSubstr(str, str) << " occurs " << it->second.first
             << " times." << endl;
        for (int const &lineNum : it->second.second) {
            cout << "(line " << lineNum << ") "
                 << highlightSubstr(_lines[lineNum - 1], str) << endl;
            //<< _lines[lineNum - 1] << endl;
        }
    }
    cout << "---------------------------------------------" << endl;
}


bool isFileExist(const string &filename) {
    std::ifstream ifs(filename);
    bool exist = ifs.is_open( );
    ifs.close( );
    return exist;
}
int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "ERROR: Args not match." << endl;
        return 1;
    }

    if (!isFileExist(argv[1])) {
        cout << "ERROR: File not exist." << endl;
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
