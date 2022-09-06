//
// Created by ms on 2022/9/1.
//

#include "Logger.h"
#include "../config/Parse.h"
#include <stdio.h>

namespace log4cpp2 {
    void Logger::initParam(std::map<std::string, std::string> &param) {
        this->name = param[Parse::param_name];
        this->additivity = param[Parse::param_additivity].empty() || StrUtils::toBool(param[Parse::param_additivity]);
    }

    void Logger::log(Level &level, Marker *marker, std::string msg, ...) {
        //TODO
//        va_list arg_ptr;
//        va_start(arg_ptr, fmt);
//        std::string str = StrUtils::format(fmt.c_str(), arg_ptr);
//        va_end(arg_ptr);
        va_list arg;
        va_start(arg, msg);
        if (isEnable(level, marker, msg, arg)) {
            logMessage(level, marker, messageFactory->newMessage(msg, arg));
        }
        va_end(arg);
    }

    void Logger::log(Level &level, Marker *marker, Message *msg) {
        if (isEnable(level, marker, msg)) {
            logMessage(level, marker, msg);
        }
    }

    void Logger::log(Level &level, Message *msg) {
        log(level, nullptr, msg);
    }

    void Logger::log(Level &level, std::string msg, ...) {
        va_list arg;
        va_start(arg, msg);
        if (isEnable(level, nullptr, msg, arg)) {
            logMessage(level, nullptr, messageFactory->newMessage(msg, arg));
        }
        va_end(arg);
    }
} // log4cpp2