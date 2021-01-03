//
// Created by yons on 2020/12/9.
//

#ifndef _INTEGER_HPP
#define _INTEGER_HPP
#include "object.hpp"
#include "string.hpp"

class Integer : public Object {
private:
    int _value;

public:
    Integer(int x){
        _value=x;
    }
    inline int value() { return _value; }

    inline const char* toString(){
        char * str = new char[64];
        String::int2String(_value,str,10);
        return str;
    }
};
#endif //_INTEGER_HPP
