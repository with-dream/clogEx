//
// Created by ms on 2022/9/4.
//

#include "LogManager.h"
#include "./config/TinyXmlParse.h"
#include "./utils/FileUtils.h"
#include "message/FormatMessageFactory.h"

namespace log4cpp2 {
    int LogManager::init(const char *path, Parse *parse, ConfigFactory *factory) {
        Param param;
        parse->parse(path, &param);
        doConfig(param, factory);

        defaultMessageFactory = new FormatMessageFactory();
        return 0;
    }

    int LogManager::init(const char *path) {
        std::string suffix = FileUtils::getFileSuffix(path);
        Parse *parse = nullptr;
        if (StrUtils::icompare("xml", suffix)) {
            parse = new TinyXmlParse();
        }

        if (!parse) {
            return -1;
        }

        init(path, parse, new ConfigFactory());
        return 0;
    }

    void LogManager::release() {

    }

    void LogManager::doConfig(Param &param, ConfigFactory *factory) {
        factory->createConfig(&config, param);
    }

    Logger *LogManager::getLogger(const char *name) {
        return getLogger(name, defaultMessageFactory);
    }

    Logger *LogManager::getLogger(const char *name, MessageFactory *factory) {
        const std::string str(name);
        auto pair = std::make_pair(str, factory->getTag());
        Logger *logger = loggerMap[pair];
        if (logger) return logger;

        std::string section(name);
        while (!section.empty()) {
            LoggerContext *lc = config.loggerContext[section];
            if (lc) {
                logger = lc->createLogger(str, factory);
                loggerMap[pair] = logger;
                return logger;
            }

            section = StrUtils::removeLastSection(section);
        }

        logger = config.rootLoggerContext->createLogger(str, factory);
        loggerMap[pair] = logger;
        return logger;
    }
} // log4cpp2