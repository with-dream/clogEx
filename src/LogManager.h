//
// Created by ms on 2022/9/4.
//

#ifndef LOGEX_LOG_H
#define LOGEX_LOG_H

#include "./config/Parse.h"
#include "./message/MessageFactory.h"
#include "./config/ConfigFactory.h"

namespace log4cpp2 {

    class LogManager {
    protected:
        std::map<std::pair<std::string, MessageFactory *>, Logger *> loggerMap;
    public:
        Config config;

    protected:
        void doConfig(Param &param, ConfigFactory *factory);
    public:
        int init(const char *path, Parse *parse, ConfigFactory *factory);
        int init(const char *path);
        void release();

        Logger *getLogger(const char *name);
        Logger *getLogger(const char *name, MessageFactory &factory);
    };

} // log4cpp2

#endif //LOGEX_LOG_H
