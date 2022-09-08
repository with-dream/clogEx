//
// Created by ms on 2022/9/7.
//

#include "FilterUtils.h"

namespace log4cpp2 {

    Result FilterUtils::filter(std::vector<Filter *> &filters, const Level &level, Marker *marker, Message *msg) {
        Result res;
        for (auto &it: filters) {
            res = it->filter(level, marker, msg);
            if (res == ACCEPT || res == DENY)
                break;
        }
        return res;
    }

    Result
    FilterUtils::filter(std::vector<Filter *> &filters, const Level &level, Marker *marker, std::string msg, ...) {
        Result res;
        va_list args;
        va_start(args, msg);

        for (auto &it: filters) {
            res = it->filter(level, marker, msg, args);
            if (res == ACCEPT || res == DENY)
                break;
        }
        va_end(args);
        return res;
    }

    Result FilterUtils::filter(std::vector<Filter *> &filters, LogEvent *logEvent) {
        Result res;
        for (auto &it: filters) {
            res = it->filter(logEvent);
            if (res == ACCEPT || res == DENY)
                break;
        }
        return res;
    }
}