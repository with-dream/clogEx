//
// Created by ms on 2022/9/18.
//

#ifndef LOGEX_WRITER_H
#define LOGEX_WRITER_H

#include "../../interceptors/Interceptor.h"

namespace log4cpp2 {

    class Writer : public Interceptor {
        bool handle(TempParam *param);
        virtual void log(TempParam *param) = 0;
    };

} // log4cpp2

#endif //LOGEX_WRITER_H
