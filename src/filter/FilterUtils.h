//
// Created by ms on 2022/9/7.
//

#ifndef LOGEX_FILTERUTILS_H
#define LOGEX_FILTERUTILS_H

#include "../config/Level.h"
#include "../marker/Marker.h"
#include "../message/Message.h"
#include "FilterResult.h"
#include <vector>

namespace log4cpp2 {
    class LogEvent;
    class Filter;
    class FilterUtils {
    public:
        static Result filter(std::vector<Filter *> &filters, const Level &level, Marker *marker, Message *msg);

        static Result filter(std::vector<Filter *> &filters, const Level &level, Marker *marker, std::string msg, ...);

        static Result filter(std::vector<Filter *> &filters, LogEvent *logEvent);

        static bool accept(Result &res);
    };
}

#endif //LOGEX_FILTERUTILS_H
