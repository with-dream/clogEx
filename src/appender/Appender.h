//
// Created by ms on 2022/8/31.
//

#ifndef LOGEX_APPENDER_H
#define LOGEX_APPENDER_H


#include <string>
#include <vector>
#include <map>
#include "../filter/Filter.h"
#include "../layout/Layout.h"
#include "../policy/Policy.h"
#include "../filter/FilterUtils.h"

namespace log4cpp2 {
    class Appender {
    public:
        std::string name;
        std::vector<Filter *> filters;
        std::map<const std::string, Filter *> refFilters;
        Layout *layout;
        std::vector<Policy *> policies;
    public:
        void callAppender(LogEvent *logEvent);
        virtual void realCallAppender(LogEvent *logEvent) = 0;
    };
}

#endif //LOGEX_APPENDER_H
