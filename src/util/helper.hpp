//
// Created by euraxluo on 2021/1/1.
//

#ifndef SIMPLE_PYVM_TIMEFORMAT_HPP
#define SIMPLE_PYVM_TIMEFORMAT_HPP

#include <time.h>
#include "string.hpp"

class Helper {
public:
    static String* timestamp2time(long timestamp) {
        auto p = gmtime(&timestamp);
        char s[100];
        strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", p);
        String * time =new String(s);
        return time;
    }

    static String* string2hex(String *str,int radix=16) {
        if (str->length() == 0) {
            String *res = new String("\000");
            return res;
        }
        size_t size = str->length() * 2;
        auto *hex_res = new String(size);
        static const char *hex = "0123456789ABCDEF";
        for (int i = 0; i < str->length(); ++i) {
            hex_res->insert(i * 2, hex[(str->c_str()[i] >> 4) & 0xf]);
            hex_res->insert(((i * 2) + 1), hex[str->c_str()[i] & 0xf]);
        }
        return hex_res;
    }
    static int byte2int(char byte) {
        return (byte&0xFF);
    }
};


#endif //SIMPLE_PYVM_TIMEFORMAT_HPP
