//
// Created by ms on 2022/9/7.
//

#include "FilterUtils.h"

namespace log4cpp2 {

    Result FilterUtils::filter(std::vector<Filter *> &filters, Level &level, Marker *marker, Message *msg) {
        Result res;
        for (auto &it:filters) {
            res = it->filter(level, marker, msg);
            if (res == ACCEPT || res == DENY)
                break;
        }
        return res;
    }

    Result FilterUtils::filter(std::vector<Filter *> &filters, Level &level, Marker *marker, std::string msg, ...) {
        Result res;
        va_list arg;
        va_start(arg, msg);

        for (auto &it:filters) {
            res = it->filter(level, marker, msg, arg);
            if (res == ACCEPT || res == DENY)
                break;
        }
        va_end(arg);
        return res;
    }

    Result FilterUtils::filter(std::vector<Filter *> &filters, LogEvent *logEvent) {
        Result res;
        for (auto &it:filters) {
            res = it->filter(logEvent);
            if (res == ACCEPT || res == DENY)
                break;
        }
        return res;
    }
}