//
// Created by euraxluo on 2021/3/11.
//


#include "runtime/cellObject.hpp"
#include "string.hpp"
#include "map.hpp"

CellKlass* CellKlass::_instance = nullptr;

CellKlass* CellKlass::getInstance() {
    if (_instance == nullptr) {
        _instance = new CellKlass();
    }

    return _instance;
}

CellKlass::CellKlass() {
    set_klass_dict(new Map());
    setName(new String("cell"));
}

CellObject::CellObject(ArrayList<Object*>* t, int i) :
        _table(t),
        _index(i) {
    setKlass(CellKlass::getInstance());
}

Object* CellObject::value() {
    return _table->get(_index);
}

size_t CellKlass::size() {
    return sizeof(CellKlass);
}

//void CellKlass::oops_do(OopClosure* closure, HiObject* obj) {
//    CellObject* co = (CellObject*)obj;
//    closure->do_oop((HiObject**)&co->_table);
//}


