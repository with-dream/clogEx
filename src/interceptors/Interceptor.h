//
// Created by ms on 2022/9/18.
//

#ifndef LOGEX_INTERCEPTOR_H
#define LOGEX_INTERCEPTOR_H

#include <vector>
#include "TempParam.h"

namespace log4cpp2 {

    class Interceptor {
    public:
        virtual void handleNext(std::vector<Interceptor *> &intercepts, int index, TempParam *param);
        virtual bool handle(TempParam *param) = 0;
    };

    class PreHandleInterceptor : public Interceptor {
    };

    class PreWriteInterceptor : public Interceptor {
    };

} // log4cpp2

#endif //LOGEX_INTERCEPTOR_H
