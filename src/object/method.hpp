//
// Created by euraxluo on 2021/3/1.
//

#ifndef SIMPLE_PYVM_METHOD_HPP
#define SIMPLE_PYVM_METHOD_HPP


#include "object.hpp"
#include "function.hpp"


//MethodKlass
class MethodKlass : public Klass {
private:
    MethodKlass(){};

    static MethodKlass *_instance;
public:
    void initialize();
    static MethodKlass *getInstance();
};

//是对Function的一种封装
class Method : public Object {
private:
    Object *_owner;
    Function *_func;
public:
    Method(Function *func) : _owner(nullptr), _func(func) {
        setKlass(MethodKlass::getInstance());
    }

    Method(Function *func, Object *owner) : _owner(owner), _func(func) {
        setKlass(MethodKlass::getInstance());
    }

    void set_owner(Object *x) { _owner = x; }

    Object *owner() { return _owner; }

    Function *func() { return _func; }
    static bool is_function(Object*);
};


#endif //SIMPLE_PYVM_METHOD_HPP
