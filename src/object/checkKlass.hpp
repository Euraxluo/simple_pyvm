//
// Created by euraxluo on 2021/3/1.
//

#ifndef SIMPLE_PYVM_CHECKKLASS_HPP
#define SIMPLE_PYVM_CHECKKLASS_HPP

#include "object.hpp"
#include "function.hpp"
#include "method.hpp"
#include "type.hpp"

class CheckKlass {
public:
    static bool isNative(Object *x) {
        Klass* k = x->klass();
        if (k == (Klass*) NativeFunctionKlass::getInstance())
            return true;

        while (k->super() != nullptr) {
            k = k->super();
            if (k == (Klass*) NativeFunctionKlass::getInstance())
                return true;
        }
        return false;
    }

    static bool isMethod(Object *x) {

        Klass* k = x->klass();
        if (k == (Klass*) MethodKlass::getInstance())
            return true;

        while (k->super() != nullptr) {
            k = k->super();
            if (k == (Klass*) MethodKlass::getInstance())
                return true;
        }
        return false;
    }


    static bool isFunction(Object *x) {
        Klass* k = x->klass();
        if (k == (Klass*) FunctionKlass::getInstance())
            return true;

        while (k->super() != nullptr) {
            k = k->super();
            if (k == (Klass*) FunctionKlass::getInstance())
                return true;
        }

        return false;
    }
    static bool isType(Object *x) {
        Klass* k = x->klass();
        if (k == (Klass*) TypeKlass::getInstance())
            return true;

        while (k->super() != nullptr) {
            k = k->super();
            if (k == (Klass*) TypeKlass::getInstance())
                return true;
        }

        return false;
    }
};


#endif //SIMPLE_PYVM_CHECKKLASS_HPP
