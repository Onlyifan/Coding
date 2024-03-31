#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::ofstream;
using std::string;
using std::unordered_map;
using std::vector;


class ConvertFile {
  public:
    ConvertFile(const char *mapname, const char *filename, const char *outputname = "output.txt")
        : _mapName(mapname)
        , _fileName(filename)
        , _outputName(outputname) {
        ifstream ifsMap(mapname);
        ifstream ifsFile(filename);

        if (!ifsMap.is_open( )) {
            std::cerr << "ERROR: The map.txt not found." << endl;
        }
        if (!ifsFile.is_open( )) {
            std::cerr << "ERROR: The file to be converted not found" << endl;
        }


        loadMapRule(ifsMap);
        storeFile(ifsFile);
        outputFile( );
    }

  private:
    void loadMapRule(ifstream &ifsMap) {
        string line;
        string key;
        string value;
        while (std::getline(ifsMap, line)) {
            istringstream iss(line);
            iss >> key;
            std::getline(iss, value, ' ');
            std::getline(iss, value, '\n');
            _map.emplace(key, value);
            // cout << key << value << endl;
            // cout << "======" << endl;
        }
    }

    void storeFile(ifstream &ifsFile) {
        string line;
        while (std::getline(ifsFile, line)) {
            _file.emplace_back(convertRow(line));
        }
    }

    void outputFile( ) {
        ofstream ofs(_outputName);
        for (const auto &line : _file) {
            ofs << line << endl;
        }
    }

    string convertRow(const string &line) const {
        string convertedLine;
        string word;

        istringstream iss(line);
        while (iss >> word) {
            auto it = _map.find(word);
            if (it != _map.end( )) {
                convertedLine += it->second;
            } else {
                convertedLine += word;
            }
            convertedLine.push_back(' ');
        }

        convertedLine.pop_back( );
        return convertedLine;
    }


  private:
    string _mapName;
    string _fileName;
    string _outputName;
    unordered_map<string, string> _map;
    vector<string> _file;
};


int main(int argc, char *argv[]) {
    if (argc != 3 && argc != 4) {
        std::cerr << "ERROR: Args not match." << endl;
        return -1;
    }

    if (argc == 3) {
        ConvertFile ret(argv[1], argv[2]);
    } else {
        ConvertFile ret(argv[1], argv[2], argv[3]);
    }

    return 0;
}
