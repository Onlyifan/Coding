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
using std::string;
using std::vector;

class TextQuery {
  public:
    void readFile(const string &filename);
    void query(const string &str) const;

  private:
    // map<string, vector<std::pair<int, std::streampos>>> _wordmap;
    map < string, std::pair < int, setstd::streampos >>> _wordmap;
};


void TextQuery::readFile(const string &filename) {
    std::ifstream ifs(filename);
    if (!ifs) {
        cout << "ERROR: Open file failed." << filename << endl;
        exit(1);
    }


    int lineIndex = 0;
    std::streampos linePos;
    char ch;
    string word;
    string line;
    while (std::getline(ifs, line)) {
        ++lineIndex;
        linePos = ifs.tellg( );

        std::istringstream iss(line);
        while (iss.get(ch)) {
            if (!isalpha(ch)) {
                continue;
            }

            word.push_back(ch);
            while (iss.get(ch) && isalpha(ch)) {
                word.push_back(ch);
            }

            vector < std::pair<int, std::streampos> &


                         word.clear( );
        }
    }

    // istringstream不打开磁盘文件, 离开作用域自动销毁
    ifs.close( );
}

void TextQuery::query(const string &str) const {}


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

    string str;
    std::cin >> str;

    map.query(str);

    return 0;
}
