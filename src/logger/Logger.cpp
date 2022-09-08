//
// Created by ms on 2022/9/1.
//

#include "Logger.h"

#include <utility>
#include "../config/Parse.h"
#include "LoggerContext.h"
#include "../message/SampleMessage.h"

namespace log4cpp2 {
    Logger::Logger() {
    }

    Logger::Logger(LoggerContext *context, const std::string &name, MessageFactory *factory)
            : logContext(context), name(name), messageFactory(factory) {

    }

    void Logger::log(const Level &level, Marker *marker, std::string msg, ...) {
        va_list args;
        va_start(args, msg);
        if (isEnable(level, marker, msg, args)) {
            logMessage(level, marker, messageFactory->newMessage(msg, args));
        }
        va_end(args);
    }

    void Logger::log(const Level &level, Marker *marker, Message *msg) {
        if (isEnable(level, marker, msg)) {
            logMessage(level, marker, msg);
        }
    }

    void Logger::log(const Level &level, Message *msg) {
        log(level, nullptr, msg);
    }

    void Logger::log(const Level &level, std::string msg, ...) {
        va_list args;
        va_start(args, msg);
        if (isEnable(level, nullptr, msg, args)) {
            logMessage(level, nullptr, messageFactory->newMessage(msg, args));
        }
        va_end(args);
    }

    bool Logger::isEnable(const Level &level, Marker *marker, Message *msg) {
        for (auto &it: this->logContext->config->filters) {
            auto res = it->filter(level, marker, msg);
            if (res != NEUTRAL)
                return res == ACCEPT;
        }
        return level >= logContext->loggerLevel;
    }

    bool Logger::isEnable(const Level &level, Marker *marker, std::string &msg, ...) {
        va_list args;
        va_start(args, msg);

        for (auto &it: this->logContext->config->filters) {
            auto res = it->filter(level, marker, msg, args);
            if (res != NEUTRAL)
                return res == ACCEPT;
        }

        va_end(args);
        return level >= logContext->loggerLevel;
    }

    void Logger::logMessage(const Level &level, Marker *marker, Message *msg) {
        std::cout << level.name << " logMessage " << ((SampleMessage *) msg)->msg << std::endl;
        auto res = FilterUtils::filter(logContext->filters, level, marker, msg);
        if (res != DENY) {
            LogEvent *logEvent = logContext->logEventFactory->createLogEvent(name, level, marker, msg);
        }
    }
} // log4cpp2