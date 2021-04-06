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

bool Method::is_function(Object *x) {
    Klass* k = x->klass();
    if (k == (Klass*) FunctionKlass::getInstance())
        return true;

    if (k->mro() == NULL)
        return false;

    for (int i = 0; i < k->mro()->size(); i++) {
        if (k->mro()->get(i) ==
            FunctionKlass::getInstance()->type()) {
            return true;
        }
    }

    return false;
}