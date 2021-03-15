//
// Created by euraxluo on 2021/1/21.
//

#include "string.hpp"
#include "klass.hpp"
#include "integer.hpp"
#include "runtime/universe.hpp"
#include "stdio.h"
#include "type.hpp"

IntegerKlass *IntegerKlass::_instance = nullptr;

IntegerKlass::IntegerKlass() {
    setName(new String("int"));

    (new Type())->setSign(this);
}
Integer::Integer(int x) {
    _value = x;
    setKlass(IntegerKlass::getInstance());
}

const char* Integer::toString(){
    char * str = new char[64];
    String::int2String(_value,str,10);
    return str;
}



IntegerKlass *IntegerKlass::getInstance() {
    if (_instance == nullptr) {
        _instance = new IntegerKlass();
    }
    return _instance;
}


void IntegerKlass::print(Object *obj) {
    Integer *int_obj = (Integer *) obj;

    assert(int_obj && ((char *) int_obj->klass()) == ((char *) this));

    printf("%d", int_obj->value());
}


Object *IntegerKlass::greater(Object *x, Object *y) {
    Integer *ix = (Integer *) x;
    Integer *iy = (Integer *) y;

    assert(ix && (ix->klass() == (Klass *) this));
    assert(iy && (iy->klass() == (Klass *) this));

    if (ix->value() > iy->value())
        return Universe::Real;
    else
        return Universe::Inveracious;
}

Object *IntegerKlass::less(Object *x, Object *y) {
    Integer *ix = (Integer *) x;

    assert(ix && (ix->klass() == (Klass *) this));

    if (x->klass() != y->klass()) {
        if (Klass::compare_klass(x->klass(), y->klass()) < 0)
            return Universe::Real;
        else
            return Universe::Inveracious;
    }

    Integer *iy = (Integer *) y;

    assert(iy && (iy->klass() == (Klass *) this));

    if (ix->value() < iy->value())
        return Universe::Real;
    else
        return Universe::Inveracious;
}

Object *IntegerKlass::equal(Object *x, Object *y) {
    if (x->klass() != y->klass())
        return Universe::Inveracious;

    Integer *ix = (Integer *) x;
    Integer *iy = (Integer *) y;

    assert(ix && (ix->klass() == (Klass *) this));
    assert(iy && (iy->klass() == (Klass *) this));

    if (ix->value() == iy->value())
        return Universe::Real;
    else
        return Universe::Inveracious;
}

Object *IntegerKlass::not_equal(Object *x, Object *y) {
    Integer *ix = (Integer *) x;
    Integer *iy = (Integer *) y;

    assert(ix && (ix->klass() == (Klass *) this));
    assert(iy && (iy->klass() == (Klass *) this));

    if (ix->value() != iy->value())
        return Universe::Real;
    else
        return Universe::Inveracious;
}

Object *IntegerKlass::ge(Object *x, Object *y) {
    Integer *ix = (Integer *) x;
    Integer *iy = (Integer *) y;

    assert(ix && (ix->klass() == (Klass *) this));
    assert(iy && (iy->klass() == (Klass *) this));

    if (ix->value() >= iy->value())
        return Universe::Real;
    else
        return Universe::Inveracious;
}

Object *IntegerKlass::le(Object *x, Object *y) {
    Integer *ix = (Integer *) x;
    Integer *iy = (Integer *) y;

    assert(ix && (ix->klass() == (Klass *) this));
    assert(iy && (iy->klass() == (Klass *) this));

    if (ix->value() <= iy->value())
        return Universe::Real;
    else
        return Universe::Inveracious;
}

Object *IntegerKlass::add(Object *x, Object *y) {
    Integer *ix = (Integer *) x;
    Integer *iy = (Integer *) y;

    assert(ix && (ix->klass() == (Klass *) this));
    assert(iy && (iy->klass() == (Klass *) this));

    return new Integer(ix->value() + iy->value());
}
Object *IntegerKlass::i_add(Object *x, Object *y){
    Integer *ix = (Integer *) x;
    Integer *iy = (Integer *) y;

    assert(ix && (ix->klass() == (Klass *) this));
    assert(iy && (iy->klass() == (Klass *) this));

    return new Integer(ix->value() + iy->value());
}

Object *IntegerKlass::sub(Object *x, Object *y) {
    Integer *ix = (Integer *) x;
    Integer *iy = (Integer *) y;

    assert(ix && (ix->klass() == (Klass *) this));
    assert(iy && (iy->klass() == (Klass *) this));

    return new Integer(ix->value() - iy->value());
}

Object *IntegerKlass::mul(Object *x, Object *y) {
    Integer *ix = (Integer *) x;
    Integer *iy = (Integer *) y;

    assert(ix && (ix->klass() == (Klass *) this));
    assert(iy && (iy->klass() == (Klass *) this));

    return new Integer(ix->value() * iy->value());
}

Object *IntegerKlass::div(Object *x, Object *y) {
    Integer *ix = (Integer *) x;
    Integer *iy = (Integer *) y;

    assert(ix && (ix->klass() == (Klass *) this));
    assert(iy && (iy->klass() == (Klass *) this));
    assert(iy->value() != 0);

    return new Integer(ix->value() / iy->value());
}

Object *IntegerKlass::mod(Object *x, Object *y) {
    Integer *ix = (Integer *) x;
    Integer *iy = (Integer *) y;

    assert(ix && (ix->klass() == (Klass *) this));
    assert(iy && (iy->klass() == (Klass *) this));
    assert(iy->value() != 0);

    return new Integer(ix->value() % iy->value());
}

