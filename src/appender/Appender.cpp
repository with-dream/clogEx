//
// Created by ms on 2022/8/31.
//

#include "Appender.h"
#include "../utils/L.h"

namespace log4cpp2 {
    void Appender::callAppender(LogEvent *logEvent) {
        if (refFilters.count(name)) {
            Result res = refFilters[name]->filter(logEvent);
            if (!FilterUtils::accept(res)) return;
        }

        Result res = FilterUtils::filter(filters, logEvent);
        if (!FilterUtils::accept(res)) return;

        L::l("callAppender==>" + logEvent->getMsg());

        auto param = new TempParam(true);
        param->logEvent = logEvent;
        intercepts[0]->handleNext(intercepts, 0, param);
    }

    void Appender::start() {
        if (!preHandle.empty())
            intercepts.insert(intercepts.end(), preHandle.begin(), preHandle.end());
        if (layout)
            intercepts.push_back(layout);
        if (!preWrite.empty())
            intercepts.insert(intercepts.end(), preWrite.begin(), preWrite.end());
        intercepts.push_back(writer);
        isStarted = true;
    }

    void Appender::stop() {
        isStarted = false;
    }
}

