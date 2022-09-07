//
// Created by ms on 2022/9/7.
//

#ifndef LOGEX_FILEUTILS_H
#define LOGEX_FILEUTILS_H

#include <string>

namespace log4cpp2 {

    class FileUtils {
    public:
        static inline const std::string getFileSuffix(const char *path) {
            std::string strPath(path);
            std::string::size_type pos = strPath.rfind('.');
            std::string str = strPath.substr(pos + 1, strPath.length());
            return str;
        }

    };

} // log4cpp2

#endif //LOGEX_FILEUTILS_H
