//
// Created by ms on 2022/9/1.
//

#ifndef LOGEX_CONSOLE_H
#define LOGEX_CONSOLE_H

#include "Appender.h"
#include "../platform/console/MultipleConsole.h"

namespace log4cpp2 {
    class LogEvent;
    class Console : public Appender {
    private:
        MultipleConsole *sole;
    public:
        const static char *TAG;
        const static std::string SYSTEM_OUT;
        const static std::string SYSTEM_ERR;
        const static std::string SYSTEM;
        std::string target;
    public:
        Console(){}
        Console(std::map<std::string, std::string> &param);
        void realCallAppender(LogEvent *logEvent);
    };

} // log4cpp2

#endif //LOGEX_CONSOLE_H
