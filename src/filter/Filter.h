//
// Created by ms on 2022/9/1.
//

#ifndef LOGEX_FILTER_H
#define LOGEX_FILTER_H

#include "../config/Level.h"
#include "../message/LogEvent.h"
#include "FilterResult.h"

namespace log4cpp2 {
    class Marker;
    class Message;

    class Filter {
    public:
        virtual Result filter(const Level &level, Marker *marker, Message *msg);

        virtual Result filter(const Level &level, Marker *marker, std::string &msg, ...);

        virtual Result filter(LogEvent *logEvent);
    };

} // log4cpp2

#endif //LOGEX_FILTER_H
