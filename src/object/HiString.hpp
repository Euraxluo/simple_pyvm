//
// Created by euraxluo on 2020/11/24.
//

#ifndef PYTHONVM_HISTRING_HPP
#define PYTHONVM_HISTRING_HPP

#include "HiObject.hpp"
#include <string.h>

class HiString: public HiObject {
private:
    char * _value;
    int _length;
public:
    HiString(const char* x){
        _length = strlen(x);
        _value = new char[_length];
        strcpy(_value,x);
    }
    HiString(const char * x, const int length){
        _length = length;
        _value = new char[length];
        for (int i = 0; i < length; ++i) {
            /**
             * 逐个拷贝，待优化
             */
            _value[i] = x[i];
        }
    }
    const char * value(){
        return _value;
    }
    int length(){
        return _length;
    }
};


#endif //PYTHONVM_HISTRING_HPP
