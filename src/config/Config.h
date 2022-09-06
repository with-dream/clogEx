//
// Created by ms on 2022/8/14.
//

#ifndef LOGEX_CONFIG_H
#define LOGEX_CONFIG_H

#include <string>
#include <map>
#include "Level.h"
#include "../appender/Appender.h"
#include "../logger/Logger.h"
#include "Param.h"

namespace log4cpp2 {
    class Config {
    public:
        Level status;
        long monitorInterval;
        std::map<std::string, std::string> property;
        std::map<std::string, Appender *> appender;
        std::map<std::string, Logger *> logger;
    };
}
#endif //LOGEX_CONFIG_H
