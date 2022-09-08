//
// Created by ms on 2022/9/7.
//

#ifndef LOGEX_FILTERUTILS_H
#define LOGEX_FILTERUTILS_H

#include "Filter.h"
#include "../config/Level.h"
#include "../marker/Marker.h"
#include "../message/Message.h"
#include "../message/LogEvent.h"
#include <vector>

namespace log4cpp2 {
    class FilterUtils {
    public:
        static Result filter(std::vector<Filter *> &filters, const Level &level, Marker *marker, Message *msg);

        static Result filter(std::vector<Filter *> &filters, const Level &level, Marker *marker, std::string msg, ...);

        static Result filter(std::vector<Filter *> &filters, LogEvent *logEvent);
    };
}

#endif //LOGEX_FILTERUTILS_H
