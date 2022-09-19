//
// Created by ms on 2022/9/8.
//

#ifndef LOGEX_NORMALLOGEVENT_H
#define LOGEX_NORMALLOGEVENT_H

#include <string>
#include <map>
#include "LogEvent.h"
#include "../marker/Marker.h"
#include "../config/Level.h"
#include "Message.h"

namespace log4cpp2 {
    class NormalLogEvent : public LogEvent {
    public:
        std::string loggerName;
        Marker *marker;
        Level level;
        Message *message;
        std::map<std::string, std::string> *map;
        unsigned long int threadId;
        std::string threadName;
        int threadPriority;
        bool includeLocation;
        long nanoTime;
    public:
        NormalLogEvent();
        NormalLogEvent(std::string loggerName, Marker *marker, const Level &level, Message *message);
        std::string getMsg();
        Level getLevel();
    };

}

#endif //LOGEX_NORMALLOGEVENT_H
