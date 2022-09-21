//
// Created by ms on 2022/9/1.
//

#include "Console.h"

namespace log4cpp2 {
    const char *Console::TAG = CLASS_NAME(Console);
    const std::string Console::SYSTEM_OUT = "SYSTEM_OUT";
    const std::string Console::SYSTEM_ERR = "SYSTEM_ERR";
    const std::string Console::SYSTEM = "SYSTEM";

    Console::Console(std::map<std::string, std::string> &param) {
        auto itName = param.find("name");
        if (itName == param.cend()) THROW_ERR("Appender must have a name")
        this->name = itName->second;
        writer = new ConsoleWriter();

        auto itTarget = param.find("target");
        if (itTarget == param.cend())
            this->target = SYSTEM;
    }

    void Console::realCallAppender(LogEvent *logEvent) {
//        char *msg = layout->toSerializable(logEvent);
//        std::string str(msg);
//        this->sole->log(str, WARN.level);
    }
} // log4cpp2