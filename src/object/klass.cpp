//
// Created by euraxluo on 2021/3/5.
//

#include <runtime/stringTable.hpp>
#include "runtime/universe.hpp"
#include "klass.hpp"
#include "integer.hpp"
#include "string.hpp"
#include "map.hpp"
#include "list.hpp"
#include "type.hpp"
#include "runtime/interpreter.hpp"


int Klass::compare_klass(Klass *x, Klass *y) {
    if (x == y)
        return 0;

    if (IntegerKlass::getInstance() == (IntegerKlass *) x)
        return -1;
    else if (IntegerKlass::getInstance() == (IntegerKlass *) y)
        return 1;

    if (x->name()->less(y->name()) == (Object *) Universe::Real)
        return -1;
    else
        return 1;
}

//attrs
Object *Klass::create_klass(Object *attrs, Object *supers, Object *name) {
    assert(attrs->klass() == (Klass *) MapKlass::getInstance());
    assert(supers->klass() == (Klass *) ListKlass::getInstance());
    assert(name->klass() == (Klass *) StringKlass::getInstance());

    Klass *new_klass = new Klass();
    Map *klass_dict = (Map *) attrs;
    List *supers_list = (List *) supers;

    new_klass->set_klass_dict(new Dict());

    new_klass->setName((String*)name);
    if(supers_list->list()->length()>0){
        Type* super = (Type*)supers_list->list()->get(0);//这里先单继承，所以用第一个父
        new_klass->setSuper(super->sign());
    }

    Type* type_obj = new Type();
    type_obj->setSign(new_klass);

    return type_obj;
}

//attrs

Object* Klass::allocate_instance(Object* callable,ArrayList<Object *> *args) {
    Object* new_instance = new Object;
    new_instance->setKlass(((Type*)callable)->sign());
    return new_instance;
}