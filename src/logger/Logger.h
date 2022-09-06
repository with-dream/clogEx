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
#include "../message/MessageFactory.h"
#include "../filter/FilterUtils.h"

namespace log4cpp2 {

    class Logger {
    private:
        MessageFactory *messageFactory;
    public:
        std::string name;
        bool additivity;
        Level loggerLevel;
        std::vector<Appender *> appender;
        std::vector<Filter *> filters;

    public:
        void initParam(std::map<std::string, std::string> &param);

        void log(Level &level, Marker *marker, Message *msg);

        void log(Level &level, Message *msg);

        void log(Level &level, Marker *marker, std::string msg, ...);

        void log(Level &level, std::string msg, ...);

        virtual bool isEnable(Level &level, Marker *marker, Message *msg) {
            return true;
        }

        virtual bool isEnable(Level &level, Marker *marker, std::string &msg, ...) {
            return true;
        }

        virtual void logMessage(Level &level, Marker *marker, Message *msg) {

        }
//        void trace();
//        void info();
//        void debug();
//        void warn();
//        void error();
//        void fatal();
    };

} // log4cpp2

#endif //LOGEX_LOGGER_H
