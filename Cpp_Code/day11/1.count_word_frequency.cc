#include <ctype.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

struct Record {
    Record(const string &str)
        : _word(str)
        , _frequency(1) {}

    string _word;
    int _frequency;
};

class Dictionary {
  public:
    void insertWord(const string &str);
    void read(const string &filename);
    void store(const string &filename) const;

  private:
    vector<Record> _dict;
};

void Dictionary::insertWord(const string &str) {
    for (vector<Record>::iterator it = _dict.begin( ); it != _dict.end( );
         ++it) {
        int result = it->_word.compare(str);
        if (result < 0) {
            continue;
        }

        if (result == 0) {
            ++it->_frequency;
            return;
        }

        if (result > 0) {
            _dict.insert(it, Record(str));
            return;
        }
    }

    _dict.push_back(Record(str));
}

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

            insertWord(word);
            word.clear( );
        }
    }

    ifs.close( );
}

void Dictionary::store(const string &filename) const {
    std::ofstream ofs(filename);

    for (const Record &record : _dict) {
        ofs << record._word << " " << record._frequency << endl;
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

    dict.read(argv[1]);
    dict.store("Dictionary.txt");


    return 0;
}
