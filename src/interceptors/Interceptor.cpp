//
// Created by ms on 2022/9/18.
//

#include "Interceptor.h"

namespace log4cpp2 {
    void Interceptor::handleNext(std::vector<Interceptor *> &intercepts, int &index, TempParam *param) {
        if (intercepts.size() >= index)
            return;

        if (intercepts[index]->handle(param)) {
            ++index;
            handleNext(intercepts, index, param);
        }
    }
} // log4cpp2