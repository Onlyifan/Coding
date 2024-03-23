#include <ctype.h>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <time.h>
#include <utility>

using std::cout;
using std::endl;
using std::map;
using std::string;

class Dictionary {
  public:
    // bool isWord(string &str);
    void read(const string &filename);
    void store(const string &filename) const;

  private:
    map<string, int> _dict;
};

void Dictionary::read(const string &filename) {
    std::ifstream ifs(filename);
    if (!ifs) {
        cout << "ERROR: Open file failed." << filename << endl;
        exit(1);
    }

    // string word;
    // while (ifs >> word) {
    //     if (isWord(word)) {
    //         ++_dict[word];
    //     }
    // }

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

// bool Dictionary::isWord(string &str) {
//     for (int i = str.size( ) - 1; i >= 0; --i) {
//         if (!isalpha(str[i])) {
//             str.erase(i, 1);
//         }
//     }
//     return str.size( ) != 0;
// }

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


    time_t currentTime = time(NULL);
    dict.read(argv[1]);
    dict.store("Dictionary.txt");
    cout << "consume " << time(NULL) - currentTime << " s." << endl;

    return 0;
}
