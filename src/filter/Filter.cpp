//
// Created by ms on 2022/9/1.
//

#include "Filter.h"
#include "../marker/Marker.h"
#include "../message/Message.h"

namespace log4cpp2 {

    Result Filter::filter(const Level &level, Marker *marker, Message *msg) {
        return NEUTRAL;
    }

    Result Filter::filter(const Level &level, Marker *marker, std::string &msg, ...) {
        return NEUTRAL;
    }

    Result Filter::filter(LogEvent *logEvent) {
        return NEUTRAL;
    }
} // log4cpp2