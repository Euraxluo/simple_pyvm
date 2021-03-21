//
// Created by euraxluo on 2021/1/16.
//

#ifndef SIMPLE_PYVM_OBJECT_HPP
#define SIMPLE_PYVM_OBJECT_HPP

#include "assert.h"
#include "klass.hpp"
class Klass;
class Map;
class ObjectKlass : public Klass{
private:
    ObjectKlass();
    static ObjectKlass* _instance;
public:
    static ObjectKlass* getInstance();
};


class Object {
private:
    Klass *_klass = nullptr;
    Map* _obj_dict = nullptr;
public:
    Klass *klass() {
        assert(_klass != nullptr);
        return _klass;
    }

    void setKlass(Klass *k) { _klass = k; }
    Map* obj_dict(){ return _obj_dict;}
    void set_obj_dict(Map* obj_dict){ _obj_dict = obj_dict;}

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
    Object* len();
    Object* abs();
    Object* pow(Object* rhs);
    Object* complex();
    Object* int_func();
    Object* float_func();
    Object* hex();
    Object* oct();
    Object* hash();

    //method sup
    Object* getattr(Object* x);
    Object* setattr(Object* k,Object* v);


};

#endif //SIMPLE_PYVM_OBJECT_HPP
