//
// Created by yons on 2020/12/9.
//

#ifndef _INTEGER_HPP
#define _INTEGER_HPP
#include "object.hpp"
class Integer : public Object {
private:
    int _value;

public:
    Integer(int x);
    int value() { return _value; }
};
#endif //_INTEGER_HPP
