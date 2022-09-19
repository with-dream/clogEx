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

        auto param = new TempParam(true);
        param->logEvent = logEvent;
        intercepts[0]->handle(param);/start()未调用
    }

    void Appender::start() {
        if (!preHandle.empty())
            intercepts.insert(intercepts.end(), preHandle.begin(), preHandle.end());
        if (layout)
            intercepts.push_back(layout);
        if (!preWrite.empty())
            intercepts.insert(intercepts.end(), preWrite.begin(), preWrite.end());
        intercepts.push_back(writer);
    }

    void Appender::stop() {

    }
}

