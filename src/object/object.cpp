//
// Created by euraxluo on 2021/1/16.
//

#include <runtime/universe.hpp>
#include <util/helper.hpp>
#include "object.hpp"
#include "klass.hpp"
#include "method.hpp"
#include "checkKlass.hpp"
#include "map.hpp"

ObjectKlass* ObjectKlass::_instance = NULL;

void ObjectKlass::initialize() {
    set_klass_dict(new Map());
    (new Type())->setSign(this);
    setName(new String("object"));//新建一个类型
    setSuper(nullptr);
}

ObjectKlass* ObjectKlass::getInstance(){
    if ( _instance == NULL)
        _instance = new ObjectKlass();

    return _instance;
}

void  Object::print() {
    klass()->print(this);
}

Object *Object::get_klass_attr(Object *x) {
    return klass()->get_klass_attr(this, x);
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

Object *Object::contains(Object* rhs){
    return klass()->contains(this, rhs);
};

Object *Object::not_contains(Object *rhs) {
    return klass()->not_contains(this, rhs);
};




Object* Object::getattr(Object* x) {
    return klass()->getattr(this,x);
}

Object* Object::setattr(Object* k,Object* v) {
    return klass()->setattr(this,k,v);
}

Object* Object::subscr(Object *x) {
    return klass()->subscr(this,x);
}

void Object::store_subscr(Object *x,Object *y) {
    return klass()->store_subscr(this,x,y);
}
void Object::del_subscr(Object *x) {
    return klass()->del_subscr(this,x);
}

Object* Object::iter() {
    return klass()->iter(this);
}

Object * Object::len() {
    return klass()->len(this);
}
Object * Object::abs() {
    return klass()->abs(this);
}
Object * Object::pow(Object* rhs) {
    return klass()->pow(this,rhs);
}
Object * Object::complex() {
    return klass()->complex(this);
}
Object * Object::int_func() {
    return klass()->int_func(this);
}
Object * Object::float_func() {
    return klass()->float_func(this);
}
Object * Object::hex() {
    return klass()->hex(this);
}

Object * Object::oct() {
    return klass()->oct(this);
}

Object * Object::hash() {
    return klass()->hash_func(this);
}
