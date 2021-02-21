//
// Created by euraxluo on 2021/1/31.
//

#include "function.hpp"

FunctionKlass *FunctionKlass::_instance = nullptr;

FunctionKlass::FunctionKlass() {}

Function::Function(Object *code_object) {
    _func_code = (CodeObject *) code_object;
    _func_name = _func_code->_co_name;
    _flags = _func_code->_flag;
    _defaults= nullptr;
    _globals= nullptr;
    setKlass(FunctionKlass::getInstance());

}

const char *Function::toString() {
    return func_name()->c_str();
}

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