//
// Created by ms on 2022/9/4.
//

#include "ConfigFactory.h"

#include "../appender/Console.h"
#include "../filter/ThresholdFilter.h"
#include "../layout/PatternLayout.h"
#include "Parse.h"
#include "../filter/ListWrapFilter.h"

namespace log4cpp2 {
    void ConfigFactory::createAppenderList(Config *config, std::vector<Param *> &appVector) {
        for (auto &it: appVector) {
            Appender *app = createAppender(it);
            if (!app) {
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

    void
    ConfigFactory::createAppenderItem(std::string &tag, std::map<std::string, std::string> &param, Appender *appender) {
        if (StrUtils::icompare(tag, PatternLayout::TAG)) {
            appender->layout = new PatternLayout(param);
        }
    }

    Filter *ConfigFactory::createFilter(Param *param) {
        if (StrUtils::icompare(param->tag, Parse::Filters)) {
            if (!param->child.empty()) {
                auto filterList = new ListWrapFilter();
                for (auto it:param->child) {
                    Filter *filter = createFilter(it);
                    filterList->addFilter(filter);
                }
                return filterList;
            }
            return nullptr;
        } else if (StrUtils::icompare(param->tag, ThresholdFilter::TAG)) {
            return new ThresholdFilter(param->attr);
        }
        return nullptr;
    }

    void ConfigFactory::createAppenderItemList(std::vector<Param *> &item, Appender *appender) {
        for (auto &it: item) {
            Filter *filter = createFilter(it);
            if (filter) {
                appender->filters.push_back(filter);
            } else {
                createAppenderItem(it->tag, it->attr, appender);
            }
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
            } else {
                Filter *filter = createFilter(it);
                if (filter) {
                    config->filters.push_back(filter);
                } else {
                    //TODO
                }
            }
        }
        return 0;
    }

    void ConfigFactory::createLoggerList(Config *config, std::vector<Param *> &child) {
        for (auto &it: child) {
            if (StrUtils::icompare(it->tag, Parse::Logger)
                || StrUtils::icompare(it->tag, Parse::Root)) {
                auto logger = createLogger(config, it);
                config->loggerContext[logger->name] = logger;

                if (StrUtils::icompare(it->tag, Parse::Root)) {
                    config->rootLoggerContext = logger;
                }
            } else {
                //TODO
            }
        }
    }

    LoggerContext *ConfigFactory::createLogger(Config *config, Param *param) {
        auto logger = new LoggerContext();
        logger->initParam(config, param->attr);

        for (auto &it: param->child) {
            if (StrUtils::icompare(it->tag, Parse::AppenderRef)) {
                std::string ref = it->attr[Parse::param_ref];
                Appender *appender = config->appender[ref];
                logger->appender.push_back(appender);

                if (!it->child.empty()) {
                    for (auto &filterIt:it->child) {
                        Filter *filter = createFilter(filterIt);
                        if (filter) {
                            appender->refFilters[param->attr[Parse::param_name]] = filter;
                        }
                    }
                }
            } else {
                Filter *filter = createFilter(it);
                if (filter) {
                    logger->filters.push_back(filter);
                }
            }
        }
        return logger;
    }

} // log4cpp2