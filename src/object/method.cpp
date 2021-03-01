//
// Created by euraxluo on 2021/3/1.
//

#include "method.hpp"
MethodKlass* MethodKlass::_instance= nullptr;
MethodKlass::MethodKlass() {
    set_klass_dict(new Dict);
}
MethodKlass* MethodKlass::getInstance() {
    if(_instance== nullptr)
        _instance = new MethodKlass();
    return _instance;
}

