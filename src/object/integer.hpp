//
// Created by yons on 2020/12/9.
//

#ifndef _INTEGER_HPP
#define _INTEGER_HPP
#include "object.hpp"
#include "string.hpp"
#include "runtime/universe.hpp"
class Universe;

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

    inline void print(){
        printf("%d",_value);
    }
    inline Object* add(Object* x){
        return new Integer(_value+((Integer*) x)->_value );
    }
    inline Object* i_add(Object* x){
        return new Integer(_value+((Integer*) x)->_value );
    }

    inline Object* greater  (Object* x) {
        if(_value>((Integer*)x)->_value)
            return Universe::Real;
        else
            return Universe::Inveracious;
    }
    inline Object* less     (Object* x) {
        if(_value<((Integer*)x)->_value)
            return Universe::Real;
        else
            return Universe::Inveracious;
    }
    inline Object* equal    (Object* x) {
        if(_value==((Integer*)x)->_value)
            return Universe::Real;
        else
            return Universe::Inveracious;

    }
    inline Object* not_equal(Object* x) {
        if(_value!=((Integer*)x)->_value)
            return Universe::Real;
        else
            return Universe::Inveracious;
    }
    inline Object* ge       (Object* x) {
        if(_value>=((Integer*)x)->_value)
            return Universe::Real;
        else
            return Universe::Inveracious;
    }
    inline Object* le       (Object* x) {
        if(_value<=((Integer*)x)->_value)
            return Universe::Real;
        else
            return Universe::Inveracious;
    }
};
#endif //_INTEGER_HPP
