//
// Created by ms on 2022/9/15.
//

#include "FormatInfo.h"
#include "../../../utils/L.h"
#include<string>

namespace log4cpp2 {
    void FormatInfo::print() {
        L::l("FormatInfo fullKey:" + fullKey + "  key:" + key + " min:" + min + " max:" + max + " param:" + param);
    }
} // log4cpp2