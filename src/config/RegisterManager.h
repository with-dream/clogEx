//
// Created by ms on 2022/9/21.
//

#ifndef LOGEX_REGISTERMANAGER_H
#define LOGEX_REGISTERMANAGER_H

#include "../handle/layout/converter/FormatConverter.h"

namespace log4cpp2 {

    class RegisterManager {
    public:
        static FormatConverter *getConverter(std::string &key);
    };

} // log4cpp2

#endif //LOGEX_REGISTERMANAGER_H
