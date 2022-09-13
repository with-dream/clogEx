//
// Created by ms on 2022/9/8.
//

#ifndef LOGEX_LOGEVENTFACTORY_H
#define LOGEX_LOGEVENTFACTORY_H

#include <string>
#include <map>
#include "LogEvent.h"
#include "../marker/Marker.h"
#include "../config/Level.h"
#include "Message.h"

namespace log4cpp2 {

    class LogEventFactory {
    public:
        virtual LogEvent *createLogEvent(std::string &loggerName, const Level &level, Marker *marker, Message *msg, std::map<std::string, std::string> &properties);
    };

} // log4cpp2

#endif //LOGEX_LOGEVENTFACTORY_H
