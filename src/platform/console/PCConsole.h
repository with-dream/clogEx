//
// Created by ms on 2022/9/13.
//

#ifndef LOGEX_PCCONSOLE_H
#define LOGEX_PCCONSOLE_H

#include <string>
namespace log4cpp2 {

    class PCConsole {
    public:
        void realLog(std::string &msg, int level);
    };

} // log4cpp2

#endif //LOGEX_PCCONSOLE_H
