//
// Created by euraxluo on 2021/1/16.
//

#include "object.hpp"
#include "klass.hpp"
void  Object::print() {
    klass()->print(this);
}

Object *Object::add(Object *rhs) {
    return klass()->add(this, rhs);
}
Object *Object::i_add(Object *rhs) {
    return klass()->i_add(this, rhs);
}

Object *Object::sub(Object *rhs) {
    return klass()->sub(this, rhs);
}

Object *Object::mul(Object *rhs) {
    return klass()->mul(this, rhs);
}

Object *Object::div(Object *rhs) {
    return klass()->div(this, rhs);
}

Object *Object::mod(Object *rhs) {
    return klass()->mod(this, rhs);
}

//Object *Object::i_add(Object *x) {}

Object *Object::greater(Object *rhs) {
    return klass()->greater(this, rhs);
};

Object *Object::less(Object *rhs) {
    return klass()->less(this, rhs);
};

Object *Object::equal(Object *rhs) {
    return klass()->equal(this, rhs);
};

Object *Object::not_equal(Object *rhs) {
    return klass()->not_equal(this, rhs);
};

Object *Object::ge(Object *rhs) {
    return klass()->ge(this, rhs);
};

Object *Object::le(Object *rhs) {
    return klass()->le(this, rhs);
};