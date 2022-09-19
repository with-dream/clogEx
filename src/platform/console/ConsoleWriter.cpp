//
// Created by ms on 2022/9/13.
//

#include "ConsoleWriter.h"

namespace log4cpp2 {
    ConsoleWriter::ConsoleWriter() {
        console = new PCConsole();
    }

    void ConsoleWriter::log(TempParam *param) {
        console->realLog(param->logEvent->getMsg(), param->logEvent->getLevel().level);
    }

}