//
// Created by ms on 2022/8/31.
//

#ifndef LOGEX_APPENDER_H
#define LOGEX_APPENDER_H


#include <string>
#include <vector>
#include <map>
#include "../filter/Filter.h"
#include "../policy/Policy.h"
#include "../filter/FilterUtils.h"
#include "../interceptors/Interceptor.h"
#include "../handle/layout/Layout.h"
#include "../handle/writer/Writer.h"

namespace log4cpp2 {
    class Appender {
    public:
        std::string name;
        std::vector<Filter *> filters;
        std::map<const std::string, Filter *> refFilters;
        Layout *layout;
        Writer *writer;
        std::vector<PreHandleInterceptor *> preHandle;
        std::vector<PreWriteInterceptor *> preWrite;
        std::vector<Interceptor *> intercepts;
        std::vector<Policy *> policies;
        bool isStarted;
    public:
        virtual void start();
        virtual void stop();
        void callAppender(LogEvent *logEvent);
        virtual void realCallAppender(LogEvent *logEvent) = 0;
    };
}

#endif //LOGEX_APPENDER_H
