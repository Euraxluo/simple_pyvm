//
// Created by euraxluo on 2021/1/31.
//

#ifndef SIMPLE_PYVM_FUNCTION_HPP
#define SIMPLE_PYVM_FUNCTION_HPP

#include <code/codeObject.hpp>
#include "klass.hpp"
#include "object.hpp"
#include "hashMap.hpp"
//typedef
typedef ArrayList<Object*>* ObjectArr;
typedef Object* (*NativeFuncPtr)(ObjectArr args);

//FunctionKlass
class FunctionKlass : public Klass {
private:


    static FunctionKlass *_instance;

    FunctionKlass();

    ~FunctionKlass();

public:
    static FunctionKlass *getInstance();

    virtual void print(Object *obj);
};

//Function
class Function : public Object {
    friend class FunctionKlass;

    friend class FrameObject;


private:
    CodeObject *_func_code;
    String *_func_name;
    unsigned int _flags;
    HashMap<Object *, Object *> *_globals;
    ObjectArr _defaults;

    NativeFuncPtr _native_func;//函数指针

public:
    enum CO_FLAGS {
        CO_VARARGS = 0x4,
        CO_VARKEYWORDS = 0x8,
        CO_GENERATOR = 0x20,
    };

    Function(Object *code_object);
    Function(NativeFuncPtr native_func_ptr);


    Object* call(ObjectArr args);
    const char *toString();

    //attr getset
    String *func_name() { return _func_name; }

    int flags() { return _flags; }

    CodeObject *func_code() { return _func_code; }

    HashMap<Object *, Object *> * globals() { return _globals; }
    void set_globals(HashMap<Object *, Object *> *globals) { _globals = globals; }

    ArrayList<Object *> *defaults() { return _defaults; }
    void set_default(ObjectArr defaults);
};

//NativeFunctionKlass
class NativeFunctionKlass: public Klass{
private:
    NativeFunctionKlass();
    static NativeFunctionKlass *_instance;
public:
    static NativeFunctionKlass *getInstance();
};

//native 方法区
Object* len(ObjectArr args);
Object* iter(ObjectArr args);
Object* type_of(ObjectArr args);
Object* isinstance(ObjectArr args);
Object* builtin_super(ObjectArr args);
Object* sysgc(ObjectArr args);

//klass 方法区
Object* upper(ObjectArr args);

#endif //SIMPLE_PYVM_FUNCTION_HPP
