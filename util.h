//
// Created by olafurj on 10/07/18.
//

#ifndef NAME_UTIL_H
#define NAME_UTIL_H
#include <string>
#include <sstream>
#include <fstream>
#include <climits>
#include <unistd.h>
class Util {
public:
    static const std::string readFile(const std::string &path) {
        std::ifstream shaderStream( path, std::ios::in );
        std::stringstream sstr;
        sstr << shaderStream.rdbuf();
        std::string src = sstr.str();
        shaderStream.close();
        return src;
    }

    static const std::string getexepath() {
        char result[PATH_MAX];
        ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
        return std::string( result, ( count > 0 ) ? count : 0 );
    }
};
#endif //NAME_UTIL_H
