//
// Created by ms on 2022/9/1.
//

#ifndef LOGEX_FILTER_H
#define LOGEX_FILTER_H

#include "../config/Level.h"
#include "../message/Message.h"
#include "../marker/Marker.h"
#include "../message/LogEvent.h"

namespace log4cpp2 {
    typedef enum _Result {
        ACCEPT, NEUTRAL, DENY
    } Result;

    class Filter {
    public:
        virtual Result filter(Level &level, Marker *marker, Message *msg) {};

        virtual Result filter(Level &level, Marker *marker, std::string &msg, ...) {};

        virtual Result filter(LogEvent *logEvent) {};
    };

} // log4cpp2

#endif //LOGEX_FILTER_H
