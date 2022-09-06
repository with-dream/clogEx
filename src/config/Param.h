//
// Created by ms on 2022/9/2.
//

#ifndef LOGEX_PARAM_H
#define LOGEX_PARAM_H

#include <map>
#include <iostream>

namespace log4cpp2 {

    class Param {
    public:
        std::string tag;
        std::map<std::string, std::string> attr;
        std::vector<Param *> child;
    public:
        void print() {
            std::cout << "tag:" << tag << std::endl;
            for (auto &it : child) {
                it->print();
            }
        }
    };

} // log4cpp2

#endif //LOGEX_PARAM_H
