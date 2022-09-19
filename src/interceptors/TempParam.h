//
// Created by ms on 2022/9/19.
//

#ifndef LOGEX_TEMPPARAM_H
#define LOGEX_TEMPPARAM_H

#include "../message/LogEvent.h"

namespace log4cpp2 {

    class TempParam {
    public:
        bool isNext;
        LogEvent *logEvent;
        void *param;
    public:
        TempParam() = default;
        TempParam(bool isNext);
    };

} // log4cpp2

#endif //LOGEX_HANDLERESULT_H
