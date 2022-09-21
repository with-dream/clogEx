//
// Created by ms on 2022/9/13.
//

#include "ConsoleWriter.h"

namespace log4cpp2 {
    ConsoleWriter::ConsoleWriter() {
        console = new PCConsole();
    }

    void ConsoleWriter::log(TempParam *param) {
        auto tmp = (std::string *)param->param;
        console->realLog(*tmp, param->logEvent->getLevel().level);
    }
}