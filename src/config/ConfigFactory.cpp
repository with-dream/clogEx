//
// Created by ms on 2022/9/4.
//

#include "ConfigFactory.h"

#include "../utils/StrUtils.h"
#include "../appender/Console.h"
#include "../filter/ThresholdFilter.h"
#include "../layout/PatternLayout.h"
#include "Parse.h"
#include "../utils/Exception.h"

namespace log4cpp2 {
    void ConfigFactory::createAppenderList(Config *config, std::vector<Param *> &appVector) {
        for (auto &it: appVector) {
            Appender *app = createAppender(it);
            if(!app) {
                //TODO
                continue;
            }
            createAppenderItemList(it->child, app);
            config->appender[app->name] = app;
        }
    }

    Appender *ConfigFactory::createAppender(Param *param) {
        Appender *res = nullptr;
        if (StrUtils::icompare(param->tag, Console::TAG)) {
            res = new Console(param->attr);
        }

        return res;
    }

    void ConfigFactory::createAppenderItem(std::string &tag, std::map<std::string, std::string> &param, Appender *appender) {
        if (StrUtils::icompare(tag, ThresholdFilter::TAG)) {
            appender->filters.push_back(new ThresholdFilter(param));
        } else if (StrUtils::icompare(tag, PatternLayout::TAG)) {
            appender->layout = new PatternLayout(param);
        }
    }

    void ConfigFactory::createAppenderItemList(std::vector<Param *> &item, Appender *appender) {
        for (auto &it: item) {
            createAppenderItem(it->tag, it->attr, appender);
            if (!it->child.empty())
                createAppenderItemList(it->child, appender);
        }
    }

    int ConfigFactory::createConfig(Config *config, Param &param) {
        if (!StrUtils::icompare(param.tag, Parse::Configuration)) {
            THROW_ERR("the root tag is not Configuration")
        }

        std::string status = param.attr[Parse::param_status];
        config->status = LevelUtil::getValue(status, ERROR);

        std::string monitorInterval = param.attr[Parse::param_monitorInterval];
        if (!monitorInterval.empty())
            config->monitorInterval = strtoll(monitorInterval.c_str(), nullptr, 10);;

        for (auto &it: param.child) {
            if (StrUtils::icompare(it->tag, Parse::Appenders)) {
                createAppenderList(config, it->child);
            } else if (StrUtils::icompare(it->tag, Parse::Loggers)) {
                createLoggerList(config, it->child);
            } else if (StrUtils::icompare(it->tag, Parse::Properties)) {
                config->property = it->attr;
            }
        }
    }

    void ConfigFactory::createLoggerList(Config *config, std::vector<Param *> &child) {
        for (auto &it: child) {
            if (StrUtils::icompare(it->tag, Parse::Logger)
                || StrUtils::icompare(it->tag, Parse::Root)) {
                auto logger = createLogger(config, it);
                config->logger[logger->name] = logger;
            } else {
                //TODO
            }
        }
    }

    Logger *ConfigFactory::createLogger(Config *config, Param *param) {
        auto logger = new Logger();
        logger->initParam(param->attr);

        for (auto &logIt: param->child) {
            if (StrUtils::icompare(param->tag, Parse::AppenderRef)) {
                std::string ref = param->attr[Parse::param_ref];
                Appender *appender = config->appender[ref];
                logger->appender.push_back(appender);
            }
        }
        return logger;
    }
} // log4cpp2