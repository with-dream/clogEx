//
// Created by ms on 2022/9/13.
//

#include "MultipleConsole.h"

namespace log4cpp2 {
    MultipleConsole::MultipleConsole() {
        console = new PCConsole();
    }

    void MultipleConsole::log(std::string &msg, int level) {
        console->realLog(msg, level);
    }
}