//
// Created by ms on 2022/9/1.
//

#include "Layout.h"
#include "../../utils/L.h"

namespace log4cpp2 {
    bool Layout::handle(TempParam *param) {
        std::string *tmpStr = toSerializable(param->logEvent);
        param->param = (void *)tmpStr;
        return param->isNext;
    }
} // log4cpp2