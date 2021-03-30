//
// Created by euraxluo on 2021/1/21.
//

#ifndef SIMPLE_PYVM_INTEGER_HPP
#define SIMPLE_PYVM_INTEGER_HPP

#include "klass.hpp"
#include "object.hpp"
class IntegerKlass : public Klass {
private:
    static IntegerKlass *_instance;

    IntegerKlass(){};

public:
    void initialize();
    static IntegerKlass *getInstance();


    virtual void print(Object *obj);


    virtual Object *greater(Object *x, Object *y);

    virtual Object *less(Object *x, Object *y);

    virtual Object *equal(Object *x, Object *y);

    virtual Object *not_equal(Object *x, Object *y);

    virtual Object *ge(Object *x, Object *y);

    virtual Object *le(Object *x, Object *y);

    virtual Object *add(Object *x, Object *y);
    virtual Object *i_add(Object *x, Object *y);

    virtual Object *sub(Object *x, Object *y);

    virtual Object *mul(Object *x, Object *y);

    virtual Object *div(Object *x, Object *y);

    virtual Object *mod(Object *x, Object *y);

    virtual Object *allocate_instance(Object* callable,ArrayList<Object*>* args);
};


class Integer : public Object {
private:
    int _value;

public:
    Integer(int x);

    int value() { return _value; }

    const char *toString();

    unsigned int hashCode() {
        unsigned int key = (unsigned int) _value;
        key += ~(key << 15);
        key ^= (key >> 10);
        key += (key << 3);
        key ^= (key >> 6);
        key += ~(key << 11);
        key ^= (key >> 16);
        return key;
    }
};


#endif //SIMPLE_PYVM_INTEGER_HPP
