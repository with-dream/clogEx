//
// Created by ms on 2022/9/7.
//

#ifndef LOGEX_LOGEVENT_H
#define LOGEX_LOGEVENT_H

namespace log4cpp2 {
    class LogEvent {
    public:
        virtual std::string getMsg() = 0;
    };

}

#endif //LOGEX_LOGEVENT_H
