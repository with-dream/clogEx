//
// Created by ms on 2022/9/8.
//

#include "LogEventFactory.h"
#include "NormalLogEvent.h"
#include "../utils/TimeUtils.h"
#include <thread>

namespace log4cpp2 {

    LogEvent *LogEventFactory::createLogEvent(std::string &loggerName, const Level &level, Marker *marker, Message *msg, std::map<std::string, std::string> &properties) {
        auto logEvent = new NormalLogEvent(loggerName, marker, level, msg);
        //TODO
//        logEvent->includeLocation   //从哪里传进来的?
        std::hash<std::thread::id> hash;
        logEvent->threadId = hash(std::this_thread::get_id());
        logEvent->nanoTime = TimeUtils::timeStampMs();
        return logEvent;
    }
} // log4cpp2