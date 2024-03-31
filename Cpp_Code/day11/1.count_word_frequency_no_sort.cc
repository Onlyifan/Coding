// 总结
// 1 vector dict可以提前扩容避免频繁扩容
// 2 输出错误信息应该用std::cerr
// 3 cin >> word 会多次进行磁盘IO, 应该用getline代替
// 4 ifs ofs都要记得调用close()

#include <algorithm>
#include <chrono>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <time.h>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

struct Record {
    Record(const string &str)
        : _word(str)
        , _frequency(1) {}

    bool operator==(const Record &rhs) const {
        return _word == rhs._word;
    }

    bool operator<(const Record &rhs) const {
        return _word < rhs._word;
    }

    string _word;
    int _frequency;
};

class Dictionary {
  public:
    Dictionary( ) {
        _dict.reserve(20000);
    }


  public:
    void insertWord(const string &str);
    void read(const string &filename);
    void store(const string &filename) const;

  private:
    vector<Record> _dict;
};

void Dictionary::insertWord(const string &str) {
    vector<Record>::iterator it = std::find(_dict.begin( ), _dict.end( ), Record(str));

    if (it != _dict.end( )) {
        ++it->_frequency;
        return;
    }

    _dict.push_back(Record(str));
}

void Dictionary::read(const string &filename) {
    std::ifstream ifs(filename);
    if (!ifs) {
        std::cerr << "ERROR: Open file failed." << filename << endl;
        exit(1);
    }

    char ch;
    string word;
    string line;
    while (std::getline(ifs, line)) {
        std::istringstream iss(line);
        while (iss.get(ch)) {
            if (!isalpha(ch)) {
                continue;
            }

            word.push_back(tolower(ch));
            while (iss.get(ch) && isalpha(ch)) {
                word.push_back(tolower(ch));
            }

            insertWord(word);
            word.clear( );
        }
    }

    time_t currentTime = time(NULL);
    std::sort(_dict.begin( ), _dict.end( ));
    cout << "sort consume " << time(NULL) - currentTime << "s." << endl;

    ifs.close( );
}

void Dictionary::store(const string &filename) const {
    std::ofstream ofs(filename);

    for (const Record &record : _dict) {
        ofs << record._word << " " << record._frequency << endl;
    }

    ofs.close( );
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

    Dictionary dict;

    auto begin = std::chrono::high_resolution_clock::now( );
    auto duration = begin.time_since_epoch( );
    auto millis_begin = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count( );
    std::cout << "当前时间（毫秒）：" << millis_begin << std::endl;
    dict.read(argv[1]);
    auto current = std::chrono::high_resolution_clock::now( );
    duration = current.time_since_epoch( );
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count( );

    std::cout << "消耗时间（毫秒）：" << millis - millis_begin << std::endl;


    dict.store("Dictionary.txt");


    return 0;
}
