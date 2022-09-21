//
// Created by ms on 2022/9/18.
//

#include "Interceptor.h"

namespace log4cpp2 {
    void Interceptor::handleNext(std::vector<Interceptor *> &intercepts, int index, TempParam *param) {
        if (index >= intercepts.size())
            return;

        if (intercepts[index]->handle(param)) {
            handleNext(intercepts, ++index, param);
        }
    }
} // log4cpp2