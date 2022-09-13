//
// Created by ms on 2022/9/1.
//

#ifndef LOGEX_LOGGER_H
#define LOGEX_LOGGER_H

#include <vector>
#include "../config/Level.h"

namespace log4cpp2 {
    class LoggerContext;
    class MessageFactory;
    class Marker;
    class Message;
    class LogEvent;

    class Logger {
    public:
        const std::string name;
        LoggerContext *logContext;
        MessageFactory *messageFactory;
        Logger *parent;

    public:
        Logger();

        Logger(LoggerContext *context, const std::string &name, MessageFactory *factory);

        void log(const Level &level, Marker *marker, Message *msg);

        void log(const Level &level, Message *msg);

        void log(const Level &level, Marker *marker, std::string msg, ...);

        void log(const Level &level, std::string msg, ...);
//        void trace();
//        void info();
//        void debug();
//        void warn();
//        void error();
//        void fatal();

    protected:
        virtual bool isEnable(const Level &level, Marker *marker, Message *msg);

        virtual bool isEnable(const Level &level, Marker *marker, std::string &msg, ...);

        virtual void logMessage(const Level &level, Marker *marker, Message *msg);

        virtual void realLogMessage(LogEvent *logEvent);

    private:
        virtual bool filter(LogEvent *logEvent);
    };

} // log4cpp2

#endif //LOGEX_LOGGER_H
