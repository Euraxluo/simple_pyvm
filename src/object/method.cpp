//
// Created by euraxluo on 2021/3/1.
//

#include "method.hpp"
#include "type.hpp"
MethodKlass* MethodKlass::_instance= nullptr;
void MethodKlass::initialize() {
    set_klass_dict(new Map());
    (new Type())->setSign(this);
    setName(new String("method"));
    setSuper(FunctionKlass::getInstance());
}
MethodKlass* MethodKlass::getInstance() {
    if(_instance== nullptr)
        _instance = new MethodKlass();
    return _instance;
}

