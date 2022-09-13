//
// Created by ms on 2022/8/31.
//

#include "Appender.h"

namespace log4cpp2 {
    void Appender::callAppender(LogEvent *logEvent) {
        if (refFilters.count(name)) {
            Result res = refFilters[name]->filter(logEvent);
            if (!FilterUtils::accept(res)) return;
        }

        Result res = FilterUtils::filter(filters, logEvent);
        if (!FilterUtils::accept(res)) return;

        realCallAppender(logEvent);
    }
}

