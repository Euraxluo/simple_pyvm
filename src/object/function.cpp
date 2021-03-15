//
// Created by euraxluo on 2021/1/31.
//

#include "function.hpp"
#include "integer.hpp"
#include "type.hpp"
#include "runtime/universe.hpp"
//FunctionKlass
FunctionKlass *FunctionKlass::_instance = nullptr;

FunctionKlass::FunctionKlass() {}

FunctionKlass *FunctionKlass::getInstance() {
    if (_instance == nullptr) {
        _instance = new FunctionKlass();
    }
    return _instance;
}

void FunctionKlass::print(Object *obj) {
    Function *func = (Function *) obj;
    assert(func && func->klass() == (Klass *) this);
    func->func_name()->print();
}

//Function
Function::Function(Object *code_object) {
    _func_code = (CodeObject *) code_object;
    _func_name = _func_code->_co_name;
    _flags = _func_code->_flag;
    _defaults = nullptr;
    _globals = nullptr;
    _native_func = nullptr;
    _closure = nullptr;
    setKlass(FunctionKlass::getInstance());

}

Function::Function(NativeFuncPtr native_func_ptr) {
    _func_code = nullptr;
    _func_name = nullptr;
    _flags = 0;
    _defaults = nullptr;
    _globals = nullptr;
    _closure = nullptr;
    _native_func = native_func_ptr;
    setKlass(NativeFunctionKlass::getInstance());
}

Object *Function::call(ObjectArr args) {
    return (_native_func)(args);
}

const char *Function::toString() {
    return func_name()->c_str();
}

void Function::set_default(ArrayList<Object *> *defaults) {
    if (defaults == nullptr) {
        _defaults = nullptr;
        return;
    }
    _defaults = new ArrayList<Object *>(defaults->length());
    for (int i = 0; i < defaults->length(); ++i) {
        _defaults->set(i, defaults->get(i));
    }
}


void Function::set_closure(List *closure) {
    _closure = closure;
}


//NativeFunctionKlass
NativeFunctionKlass *NativeFunctionKlass::_instance = nullptr;

NativeFunctionKlass *NativeFunctionKlass::getInstance() {
    if (_instance == nullptr) {
        _instance = new NativeFunctionKlass();
    }
    return _instance;
}

NativeFunctionKlass::NativeFunctionKlass() {
    setSuper(FunctionKlass::getInstance());
}

//NativeFunctions
Object *len(ObjectArr args) {
    Object *argtmp = args->get(0);
    assert(argtmp->klass() == StringKlass::getInstance());
    return argtmp->klass()->len(argtmp);
}

Object* type_of(ObjectArr args) {
    Object* arg0 = args->get(0);
    return arg0->klass()->type();
}

Object *isinstance(ObjectArr args) {
    Object *x = args->get(0);
    Object *y = args->get(1);
    assert(y&&y->klass() == TypeKlass::getInstance());

    Klass* k = x->klass();
    while (k!= nullptr){
        if (k==((Type*)y)->sign())
            return Universe::Real;
        k = k->super();
    }
    return Universe::Inveracious;
}

//Klass Functions
Object *upper(ObjectArr args) {
    Object *argtmp = args->get(0);
    assert(argtmp->klass() == StringKlass::getInstance());
    return StringKlass::getInstance()->upper(argtmp);
}