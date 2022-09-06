//
// Created by ms on 2022/9/2.
//

#ifndef LOGEX_EXCEPTION_H
#define LOGEX_EXCEPTION_H

#include <exception>
#include <iostream>
#include <string>
#include <utility>

namespace log4cpp2 {
    class Exception : public std::exception {
    public:
        Exception(const std::string &detail)
                : m_strDetail(detail) {
        }

        const char *what() const noexcept override {
            return m_strDetail.c_str();
        }

    private:
        std::string m_strDetail;
    };

#define THROW_ERR(err) { \
    std::string s;       \
    s += "line:";                     \
    s += std::to_string(__LINE__);         \
    s += " detail:";                     \
    s += err;         \
    throw log4cpp2::Exception{s}; \
}

} // log4cpp2

#endif //LOGEX_EXCEPTION_H
