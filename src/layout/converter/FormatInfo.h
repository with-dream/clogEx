//
// Created by ms on 2022/9/15.
//

#ifndef LOGEX_FORMATINFO_H
#define LOGEX_FORMATINFO_H

#include <string>

namespace log4cpp2 {

    class FormatInfo {
    public:
        std::string fullKey;
        std::string key;
        std::string min;
        std::string max;
        std::string type;
        std::string param;
    public:
        void print();
    };

} // log4cpp2

#endif //LOGEX_FORMATINFO_H
