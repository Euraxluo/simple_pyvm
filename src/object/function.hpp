//
// Created by euraxluo on 2021/1/31.
//

#ifndef SIMPLE_PYVM_FUNCTION_HPP
#define SIMPLE_PYVM_FUNCTION_HPP

#include "klass.hpp"
#include "object.hpp"
#include "code/codeObject.hpp"

class FunctionKlass : public Klass {
private:


    static FunctionKlass *_instance;

    FunctionKlass();

    ~FunctionKlass();

public:
    static FunctionKlass *getInstance();

    virtual void print(Object *obj);
};


class Function : public Object {
    friend class FunctionKlass;

    friend class FrameObject;

private:
    CodeObject *_func_code;
    String *_func_name;
    unsigned int _flags;

public:
    Function(Object *code_object);

    String *func_name() { return _func_name; }

    int flags() { return _flags; }


    const char *toString();
};


#endif //SIMPLE_PYVM_FUNCTION_HPP
