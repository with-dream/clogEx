//
// Created by ms on 2022/9/11.
//

#ifndef LOGEX_L_H
#define LOGEX_L_H

#include <string>
#include <iostream>

namespace log4cpp2 {
    class L {
    public:
        static void l(std::string str) {
            std::cout << str << std::endl;
        }
    };
}
#endif //LOGEX_L_H
