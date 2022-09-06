//
// Created by ms on 2022/9/4.
//

#include "LogManager.h"
#include "./config/TinyXmlParse.h"

namespace log4cpp2 {
    int LogManager::init(const char *path, Parse *parse, ConfigFactory *factory) {
        Param param;
        parse->parse(path, &param);
        doConfig(param, factory);
    }

    int LogManager::init(const char *path) {

    }

    void LogManager::release() {

    }

    void LogManager::doConfig(Param &param, ConfigFactory *factory) {
        factory->createConfig(&config, param);
    }

    Logger *LogManager::getLogger(const char *name) {

    }

    Logger *LogManager::getLogger(const char *name, MessageFactory &factory) {

    }
} // log4cpp2