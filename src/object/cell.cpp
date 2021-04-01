//
// Created by euraxluo on 2021/3/11.
//


#include "cell.hpp"
#include "string.hpp"
#include "map.hpp"
#include "type.hpp"

CellKlass* CellKlass::_instance = nullptr;

CellKlass* CellKlass::getInstance() {
    if (_instance == nullptr) {
        _instance = new CellKlass();
    }

    return _instance;
}

void CellKlass::initialize() {
    set_klass_dict(new Map());
    (new Type())->setSign(this);
    setName(new String("cell"));
    setSuper(ObjectKlass::getInstance());
}

Cell::Cell(ArrayList<Object*>* t, int i) :
        _table(t),
        _index(i) {
    setKlass(CellKlass::getInstance());
}

Object* Cell::value() {
    return _table->get(_index);
}

size_t CellKlass::size() {
    return sizeof(CellKlass);
}

