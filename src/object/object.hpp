//
// Created by euraxluo on 2021/1/16.
//

#ifndef SIMPLE_PYVM_OBJECT_HPP
#define SIMPLE_PYVM_OBJECT_HPP

#include "assert.h"
class Klass;
class Object {
private:
    Klass *_klass = nullptr;
public:
    Klass *klass() {
        assert(_klass != nullptr);
        return _klass;
    }

    void setKlass(Klass *k) { _klass = k; }


    virtual const char *toString() {}

    virtual unsigned int hashCode() {}

    void print();

    Object *add(Object *rhs);

    Object *sub(Object *rhs);

    Object *mul(Object *rhs);

    Object *div(Object *rhs);

    Object *mod(Object *rhs);

    Object *i_add(Object *x);

    Object *greater(Object *rhs);

    Object *less(Object *rhs);

    Object *equal(Object *rhs);

    Object *not_equal(Object *rhs);

    Object *ge(Object *rhs);

    Object *le(Object *rhs);

    Object *contains(Object *rhs);
    Object *not_contains(Object* rhs);

    Object* subscr(Object* x);
    void store_subscr(Object* x,Object *y);
    void del_subscr(Object* x);

    //native funcion
    Object* iter();
//    Object* len();

    //method sup
    Object* getattr(Object* x);


};

#endif //SIMPLE_PYVM_OBJECT_HPP
