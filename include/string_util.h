#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <vector>
#include <string>


/**
 * string util to handle string
 */
class string_util {
public:
    // trim a string
    static std::string trim(const std::string &str);
    // split a string by delim(string)
    static std::vector<std::string> split(const std::string &line, const std::string &delim);
    // split a string by delim(char)
    static std::vector<std::string> split(const std::string &line, char delim);
};


#endif //STRING_UTIL_H
