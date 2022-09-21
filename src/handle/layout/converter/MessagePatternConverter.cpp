//
// Created by ms on 2022/9/21.
//

#include "MessagePatternConverter.h"

namespace log4cpp2 {
    void MessagePatternConverter::format(LogEvent *event, std::string &buf) {
        buf.append(event->getMsg());
    }
} // log4cpp2