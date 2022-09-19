//
// Created by ms on 2022/9/1.
//

#include "Layout.h"

namespace log4cpp2 {
    bool Layout::handle(TempParam *param) {
        auto result = new TempParam(true);
        result->param = toSerializable(param->logEvent);
        return result;
    }
} // log4cpp2