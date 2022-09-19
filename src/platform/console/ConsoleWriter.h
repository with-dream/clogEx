//
// Created by ms on 2022/9/13.
//

#ifndef LOGEX_CONSOLEWRITER_H
#define LOGEX_CONSOLEWRITER_H

#include <string>
#include "PCConsole.h"
#include "../../handle/writer/Writer.h"

namespace log4cpp2 {

    class ConsoleWriter : Writer {
    private:
        PCConsole *console;
    public:
        ConsoleWriter();

        void log(TempParam *param) override;
    };

} // log4cpp2

#endif //LOGEX_CONSOLEWRITER_H
