//
// Created by ms on 2022/9/1.
//

#ifndef LOGEX_LOGGER_H
#define LOGEX_LOGGER_H

#include <vector>
#include "../appender/Appender.h"
#include "../config/Level.h"
#include "../marker/Marker.h"
#include "../message/Message.h"

namespace log4cpp2 {

    class Logger {
    public:
        std::string name;
        bool additivity;
        Level loggerLevel;
        std::vector<Appender *> appender;
    public:
        void initParam(std::map<std::string, std::string> &param);

        void log(Level &level, Marker &marker, Message *msg);
        void log(Level &level, Message *msg);
        void log(Level &level, Marker &marker, const std::string& msg, ...);
        void log(Level &level, const std::string& msg, ...);
//        void trace();
//        void info();
//        void debug();
//        void warn();
//        void error();
//        void fatal();
    };

} // log4cpp2

#endif //LOGEX_LOGGER_H
