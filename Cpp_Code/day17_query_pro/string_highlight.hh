#ifndef _STRING_HIGHLIGHT_HH_
#define _STRING_HIGHLIGHT_HH_


#include <algorithm>
#include <string.h>
#include <string>
#include <vector>


namespace {
// red green yellow blue default
std::vector<const char *> Color = {"\033[1;31m", "\033[1;32m", "\033[1;33m",
                                   "\033[1;34m", "\033[0m"};
}; // namespace


namespace render {

inline void extractStrs(std::vector<std::string> &vec) {
    return;
};

template <typename... Args>
void extractStrs(std::vector<std::string> &vec, const std::string &firstArg,
                 Args &&...remainArgs);

template <typename... Args>
std::string highlightSubStr(const std::string &originalStr,
                            Args &&...targetSubStrs);
}; // namespace render


template <typename... Args>
void render::extractStrs(std::vector<std::string> &vec,
                         const std::string &firstArg, Args &&...remainArgs) {
    vec.push_back(firstArg);
    render::extractStrs(vec, remainArgs...);
}

template <typename... Args>
std::string render::highlightSubStr(const std::string &originalStr,
                                    Args &&...targetSubStrs) {

    uint32_t subStrsNum = sizeof...(targetSubStrs);
    std::vector<std::string> subStrs;
    subStrs.reserve(subStrsNum);
    extractStrs(subStrs, targetSubStrs...);

    std::string highlightedStr(originalStr);
    std::string loweredOriginalStr(originalStr);
    std::transform(loweredOriginalStr.begin( ), loweredOriginalStr.end( ),
                   loweredOriginalStr.begin( ), ::tolower);

    for (uint32_t i = 0; i != subStrsNum; ++i) {
        std::string loweredSubStr(std::move(subStrs[i]));
        std::transform(loweredSubStr.begin( ), loweredSubStr.end( ),
                       loweredSubStr.begin( ), ::tolower);

        size_t currentPos = 0;
        size_t nextPos;

        while ((nextPos = loweredOriginalStr.find(loweredSubStr, currentPos)) !=
               std::string::npos) {
            if ((nextPos == 0) ||
                !isalnum(loweredOriginalStr[nextPos - 1]) &&
                    ((nextPos + loweredSubStr.size( ) ==
                      loweredOriginalStr.size( )) ||
                     !isalnum(loweredOriginalStr[nextPos +
                                                 loweredSubStr.size( )]))) {
                highlightedStr.insert(nextPos, Color[i % Color.size( )]);
                loweredOriginalStr.insert(nextPos, Color[i % Color.size( )]);
                nextPos +=
                    strlen(Color[i % Color.size( )]) + loweredSubStr.size( );
                highlightedStr.insert(nextPos, Color.back( ));
                loweredOriginalStr.insert(nextPos, Color.back( ));
                currentPos = nextPos + strlen(Color.back( ));
                continue;
            }
            currentPos = nextPos + loweredSubStr.size( );
        }
    }

    return highlightedStr;
}


#endif // _STRING_HIGHLIGHT_HH_
