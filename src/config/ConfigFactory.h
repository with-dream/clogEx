//
// Created by ms on 2022/9/4.
//

#ifndef LOGEX_CONFIGFACTORY_H
#define LOGEX_CONFIGFACTORY_H

#include <map>
#include <regex>
#include <set>
#include "../appender/Appender.h"
#include "Param.h"
#include "Config.h"
#include "../lookup/Lookup.h"
#include "FormatParam.h"

namespace log4cpp2 {

    class ConfigFactory {
    private:
        const std::regex lookupRx;
        std::map<std::string, Lookup *> lookupMap;
        std::map<std::string, std::string> tmpProperty;
    public:
        ConfigFactory();

        int createConfig(Config *config, Param &param);

    private:
        Appender *createAppender(Param *param);

        void createAppenderList(Config *config, std::vector<Param *> &appVector);

        void createAppenderItemList(Config *config, std::vector<Param *> &item, Appender *appender);

        void createAppenderItem(Config *config, std::string &tag, std::map<std::string, std::string> &param,
                                Appender *appender);

        void preProperties(std::string key, std::string &value, std::map<std::string, std::string> &property,
                           std::map<std::string, FormatParam *> &tmpPattern, std::set<std::string> &set);

        Filter *createFilter(Param *param);

        void createLoggerList(Config *config, std::vector<Param *> &child);

        LoggerContext *createLogger(Config *config, Param *param);

        Lookup *createLookup(const std::string &category);

        Lookup *getLookup(const std::string &category);
    };

} // log4cpp2

#endif //LOGEX_CONFIGFACTORY_H
