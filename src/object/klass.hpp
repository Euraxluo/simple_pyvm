//
// Created by euraxluo on 2021/1/15.
//

#ifndef SIMPLE_PYVM_KLASS_HPP
#define SIMPLE_PYVM_KLASS_HPP

#include "util/arrayList.hpp"
#include "util/hashMap.hpp"

class Object;

class String;

typedef HashMap<Object *, Object *> Dict;

class Klass {
private:
    String *_name = nullptr;
    Klass *_super = nullptr;

    //用于记录某一种类型上的属性和方法
    Dict *_klass_dict = nullptr;

public:
    Klass() {}

    void setName(String *name) { _name = name; }

    void setSuper(Klass *super) { _super = super; }

    String *name() { return _name; }

    Klass *super() { return _super; }

    virtual void print(Object *obj) {};

    void set_klass_dict(Dict *dict) { _klass_dict = dict; }

    Dict *klass_dict() { return _klass_dict; }

    //类型支持函数虚拟声明
    virtual Object *greater(Object *x, Object *y) { return 0; };

    virtual Object *less(Object *x, Object *y) { return 0; };

    virtual Object *equal(Object *x, Object *y) { return 0; };

    virtual Object *not_equal(Object *x, Object *y) { return 0; };

    virtual Object *ge(Object *x, Object *y) { return 0; };

    virtual Object *le(Object *x, Object *y) { return 0; };


    virtual Object *add(Object *x, Object *y) { return 0; };

    virtual Object *i_add(Object *x, Object *y) { return 0; };

    virtual Object *sub(Object *x, Object *y) { return 0; };

    virtual Object *mul(Object *x, Object *y) { return 0; };

    virtual Object *div(Object *x, Object *y) { return 0; };

    virtual Object *mod(Object *x, Object *y) { return 0; };

    //native func define
    virtual Object *call(ArrayList<Object *> *args) { return 0; }

    virtual Object *len(Object *x) { return 0; }

    //type function
    virtual Object *subscr(Object *x, Object *y) { return 0; }
};


#endif //SIMPLE_PYVM_KLASS_HPP
