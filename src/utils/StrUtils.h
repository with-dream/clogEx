//
// Created by ms on 2022/8/31.
//

#ifndef LOGEX_STRUTILS_H
#define LOGEX_STRUTILS_H


#include <string>
#include <cctype>
#include <iostream>
#include <sstream>
#include "Exception.h"
#include <vector>

#define CLASS_NAME(name) #name

class StrUtils {
public:
    static bool icompare(const std::string &a, const std::string &b) {
        if (a.length() != b.length()) return false;
        return std::equal(a.begin(), a.end(), b.begin(),
                          [](char a, char b) {
                              return toupper(a) == toupper(b);
                          });
    }

    static bool compare(const std::string &a, const std::string &b) {
        if (a.length() != b.length()) return false;
        return std::equal(a.begin(), a.end(), b.begin(),
                          [](char a, char b) {
                              return a == b;
                          });
    }

    static bool toBool(std::string str, bool strict = false) {
        if (strict && (icompare("true", str) || icompare("false", str))) {
            THROW_ERR("toBool param err  str:" + str)
        }
        bool b;
        std::istringstream(str) >> std::boolalpha >> b;
        return b;
    }

    static bool isEmpty(const char *str) {
        return str == nullptr || !strlen(str);
    }

    static void upper(std::string &str) {
        if (str.empty()) return;
        transform(str.begin(), str.end(), str.begin(), ::toupper);
    }

    static const char *lower(std::string &str) {
        if (str.empty()) return nullptr;
        transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str.c_str();
    }

    template<typename ...Args>
    inline static std::string format(const char *format, Args... args) {
        constexpr size_t oldlen = BUFSIZ;
        char buffer[oldlen];  // 默认栈上的缓冲区

        size_t newlen = snprintf(&buffer[0], oldlen, format, args...);
        newlen++;  // 算上终止符'\0'

        if (newlen > oldlen) {  // 默认缓冲区不够大，从堆上分配
            std::vector<char> newbuffer(newlen);
            snprintf(newbuffer.data(), newlen, format, args...);
            return std::string(newbuffer.data());
        }

        std::string res(buffer);
        res.shrink_to_fit();
        return res;
    }

    static inline std::string&& removeLastSection(std::string &str) {
        std::string::size_type pos = str.rfind('.');
        std::string res = str.substr(0, pos);
        return std::move(res);
    }

    static inline std::vector<std::string> split(std::string &str, const char *s) {
        std::istringstream iss(str);
        std::string token;
        std::vector<std::string> res;
        while (getline(iss, token, ':')) {
            res.push_back(token);
        }
        return res;
    }
};

#endif //LOGEX_STRUTILS_H
