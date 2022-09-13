//
// Created by ms on 2022/9/13.
//

#ifndef LOGEX_TIMEUTILS_H
#define LOGEX_TIMEUTILS_H

#include <chrono>

class TimeUtils {
public:
    static long timeStampMs() {
        auto timeStamp =std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::system_clock::now().time_since_epoch()).count();
        return timeStamp;
    }
};


#endif //LOGEX_TIMEUTILS_H
