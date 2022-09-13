//
// Created by ms on 2022/9/13.
//

#ifndef LOGEX_MULTIPLECONSOLE_H
#define LOGEX_MULTIPLECONSOLE_H

#include <string>
#include "PCConsole.h"

namespace log4cpp2 {

    class MultipleConsole {
    private:
        PCConsole *console;
    public:
        MultipleConsole();

        void log(std::string &msg, int level);
    };

} // log4cpp2

#endif //LOGEX_MULTIPLECONSOLE_H
