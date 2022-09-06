//
// Created by ms on 2022/9/4.
//

#ifndef LOGEX_CONFIGFACTORY_H
#define LOGEX_CONFIGFACTORY_H

#include <map>
#include "../appender/Appender.h"
#include "Param.h"
#include "Config.h"

namespace log4cpp2 {

    class ConfigFactory {
    private:
    public:
        int createConfig(Config *config, Param &param);

    private:
        Appender *createAppender(Param *param);

        void createAppenderList(Config *config, std::vector<Param *> &appVector);

        void createAppenderItemList(std::vector<Param *> &item, Appender *appender);

        void createAppenderItem(std::string &tag, std::map<std::string, std::string> &param, Appender *appender);

        void createLoggerList(Config *config, std::vector<Param *> &child);

        Logger *createLogger(Config *config, Param *param);
    };

} // log4cpp2

#endif //LOGEX_CONFIGFACTORY_H
