#include "string_highlight.hh"
#include <ctype.h>
#include <sstream>

static std::string cleanStr(std::string str) {
    for (char &ch : str) {
        if (!isalnum(ch)) {
            ch = ' ';
        }
    }
    return str;
}


std::string render::highlightSubStr(const std::string &originalStr,
                                    const std::string &targetSubStr) {
    std::string cleandSubStr(cleanStr(targetSubStr));
    std::istringstream iss(cleandSubStr);


    std::string highlightedStr(originalStr);
    std::string loweredOriginalStr(originalStr);
    std::transform(loweredOriginalStr.begin( ), loweredOriginalStr.end( ),
                   loweredOriginalStr.begin( ), ::tolower);

    int colorNum = 0;
    std::string subStr;
    while (iss >> subStr) {
        std::string loweredSubStr(subStr);
        std::transform(loweredSubStr.begin( ), loweredSubStr.end( ), loweredSubStr.begin( ),
                       ::tolower);

        size_t currentPos = 0;
        size_t nextPos;

        while ((nextPos = loweredOriginalStr.find(loweredSubStr, currentPos)) !=
               std::string::npos) {
            if (((nextPos == 0) || !isalnum(loweredOriginalStr[nextPos - 1])) &&
                ((nextPos + loweredSubStr.size( ) == loweredOriginalStr.size( )) ||
                 !isalnum(loweredOriginalStr[nextPos + loweredSubStr.size( )]))) {
                highlightedStr.insert(nextPos, Color[colorNum % Color.size( )]);
                loweredOriginalStr.insert(nextPos, Color[colorNum % Color.size( )]);
                nextPos += strlen(Color[colorNum % Color.size( )]) + loweredSubStr.size( );
                highlightedStr.insert(nextPos, Color.back( ));
                loweredOriginalStr.insert(nextPos, Color.back( ));
                currentPos = nextPos + strlen(Color.back( ));
                continue;
            }
            currentPos = nextPos + loweredSubStr.size( );
        }
        ++colorNum;
    }

    return highlightedStr;
}
