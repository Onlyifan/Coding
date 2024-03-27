#ifndef _STRING_HIGHLIGHT_HH_
#define _STRING_HIGHLIGHT_HH_


#include <string>
#include <vector>


namespace {
// red green yellow blue default
std::vector<const char *> Color = {"\033[1;31m", "\033[1;32m", "\033[1;33m", "\033[1;34m",
                                   "\033[0m"};
}; // namespace


namespace render {

template <typename... Args>
std::string highlightSubStr(const std::string &originalStr, Args &&...targetSubStrs);

std::string highlightSubStr(const std::string &originalStr, const std::string &targetSubStrs);
}; // namespace render


#endif // _STRING_HIGHLIGHT_HH_
