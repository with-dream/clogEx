//
// Created by ms on 2022/9/8.
//

#include "NormalLogEvent.h"

namespace log4cpp2 {
    NormalLogEvent::NormalLogEvent() {

    }

    NormalLogEvent::NormalLogEvent(std::string loggerName, Marker *marker, Level &level, Message *message)
            : loggerName(loggerName), marker(marker), level(level), message(message) {

    }
} // log4cpp2