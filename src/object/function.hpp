//
// Created by euraxluo on 2021/1/31.
//

#ifndef SIMPLE_PYVM_FUNCTION_HPP
#define SIMPLE_PYVM_FUNCTION_HPP

#include "klass.hpp"
#include "object.hpp"
#include "hashMap.hpp"
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
    HashMap<Object *, Object *> *_globals;
    ArrayList<Object *> *_defaults;

public:
    Function(Object *code_object);

    String *func_name() { return _func_name; }

    int flags() { return _flags; }
    CodeObject *func_code() { return _func_code; }

    const char *toString();

    HashMap<Object *, Object *> *globals() { return _globals; }

    void set_globals(HashMap<Object *, Object *> *globals) { _globals = globals; }

    ArrayList<Object *> *defaults() { return _defaults; }

    void set_default(ArrayList<Object *> *defaults);
};


#endif //SIMPLE_PYVM_FUNCTION_HPP
