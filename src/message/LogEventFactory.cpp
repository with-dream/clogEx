//
// Created by ms on 2022/9/8.
//

#include "LogEventFactory.h"
#include "NormalLogEvent.h"

namespace log4cpp2 {

    LogEvent *LogEventFactory::createLogEvent(std::string &loggerName, Marker *marker, Level &level, Message *msg, std::map<std::string, std::string> &properties) {
        auto logEvent = new NormalLogEvent(loggerName, marker, level, msg);
        logEvent->includeLocation   //从哪里传进来的?
        return logEvent;
    }
} // log4cpp2