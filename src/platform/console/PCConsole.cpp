//
// Created by ms on 2022/9/13.
//

#include "PCConsole.h"
#include "../../config/Level.h"
#include <iostream>

namespace log4cpp2 {
    void PCConsole::realLog(std::string &msg, int level) {
        if (level >= WARN.level) {
            std::cerr << msg << std::endl;
        } else {
            std::cout << msg << std::endl;
        }
    }
} // log4cpp2