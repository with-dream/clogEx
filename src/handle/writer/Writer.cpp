//
// Created by ms on 2022/9/18.
//

#include "Writer.h"

namespace log4cpp2 {
    bool Writer::handle(TempParam *param) {
        log(param);
        return true;
    }
} // log4cpp2