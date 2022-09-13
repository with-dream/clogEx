//
// Created by ms on 2022/9/7.
//

#include "LoggerContext.h"
#include "../config/Parse.h"
#include "Logger.h"
#include "../config/Config.h"

namespace log4cpp2 {
    void LoggerContext::initParam(Config *config, std::map<std::string, std::string> &param) {
        this->config = config;
        this->name = param[Parse::param_name];
        this->additivity = param[Parse::param_additivity].empty() || StrUtils::toBool(param[Parse::param_additivity]);
        this->logEventFactory = new LogEventFactory();
    }

    Logger *LoggerContext::createLogger(const std::string &name, MessageFactory *factory) {
        //TODO 多种Logger
        auto logger = new Logger(this, name, factory);
        return logger;
    }
}
