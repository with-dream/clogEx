//
// Created by ms on 2022/9/7.
//

#ifndef LOGEX_LOGGERCONTEXT_H
#define LOGEX_LOGGERCONTEXT_H

#include <vector>
#include "../appender/Appender.h"
#include "../config/Level.h"
#include "../marker/Marker.h"
#include "../message/Message.h"
#include "../message/MessageFactory.h"
#include "../filter/FilterUtils.h"

namespace log4cpp2 {
    class Logger;
    class Config;
    class LoggerContext {
    public:
        Config *config;
        std::string name;
        bool additivity;
        Level loggerLevel;
        std::vector<Appender *> appender;
        std::vector<Filter *> filters;

    public:
        void initParam(Config *config, std::map<std::string, std::string> &param);
        Logger *createLogger(const std::string &name, MessageFactory *factory);
    };
}


#endif //LOGEX_LOGGERCONTEXT_H
