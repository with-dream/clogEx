//
// Created by ms on 2022/9/1.
//

#include "Logger.h"
#include "../config/Parse.h"

namespace log4cpp2 {
    void Logger::initParam(std::map<std::string, std::string> &param) {
        this->name = param[Parse::param_name];
        this->additivity = param[Parse::param_additivity].empty() || StrUtils::toBool(param[Parse::param_additivity]);
    }

    void Logger::log(Level &level, Marker &marker, const std::string &fmt, ...) {
//        va_list arg_ptr;
//        va_start(arg_ptr, fmt);
//        std::string str = StrUtils::format(fmt.c_str(), arg_ptr);
//        va_end(arg_ptr);
    }

    void Logger::log(Level &level, Marker &marker, Message *msg) {

    }

    void Logger::log(Level &level, Message *msg) {

    }

    void Logger::log(Level &level, const std::string &msg, ...) {

    }
} // log4cpp2