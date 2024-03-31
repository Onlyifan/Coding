#include <chrono>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>

using std::cout;
using std::endl;
using std::string;
using std::unordered_map;

class Dictionary {
  public:
    // bool isWord(string &str);
    void read(const string &filename);
    void store(const string &filename) const;

  private:
    unordered_map<string, int> _dict;
};

void Dictionary::read(const string &filename) {
    std::ifstream ifs(filename);
    if (!ifs) {
        cout << "ERROR: Open file failed." << filename << endl;
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

            word.push_back(ch);
            while (iss.get(ch) && isalpha(ch)) {
                word.push_back(ch);
            }

            ++_dict[word];
            word.clear( );
        }
    }

    ifs.close( );
}

void Dictionary::store(const string &filename) const {
    std::ofstream ofs(filename);

    for (const std::pair<string, int> &pair : _dict) {
        ofs << pair.first << " " << pair.second << endl;
    }
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
