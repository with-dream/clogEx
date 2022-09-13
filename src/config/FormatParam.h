//
// Created by ms on 2022/9/11.
//

#ifndef LOGEX_FORMATPARAM_H
#define LOGEX_FORMATPARAM_H

#include <string>

namespace log4cpp2 {

    class FormatParam {
    public:
        const static std::string INHERENT;
        std::string inherent;
        std::string category;
        std::string type;
        std::string param;
        bool isResult;
    public:
        FormatParam();

        FormatParam(const std::string &inherent, const std::string &category, const std::string &type);
    };

} // log4cpp2

#endif //LOGEX_FORMATPARAM_H
