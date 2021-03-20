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

void Klass::print(Object *obj) {
//    <define_class.A object at 0x7f0fc961ad10>
    printf("<");
    Map* attr_dict = obj->klass()->klass_dict();
    if ( attr_dict){
        Object* mod = attr_dict->get((Object*)StringTable::getInstance()->mod_str,Universe::None);
        if (mod != Universe::None){
            mod->print();
            printf(".");
        }
    }
    obj->klass()->name()->print();
    printf(" object at %p>", obj);
};

//attrs
Object *Klass::create_klass(Object *attrs, Object *supers, Object *name) {
    assert(attrs->klass() == (Klass *) MapKlass::getInstance());
    assert(supers->klass() == (Klass *) ListKlass::getInstance());
    assert(name->klass() == (Klass *) StringKlass::getInstance());

    Klass *new_klass = new Klass();
    Map *klass_dict = (Map *) attrs;
    List *supers_list = (List *) supers;

    new_klass->set_klass_dict(klass_dict);

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
    Object* new_instance = new Object();
    new_instance->setKlass(((Type*)callable)->sign());
    //找这个class的__init__函数
    Object* constructor = new_instance->getattr(StringTable::getInstance()->init_str);
    if (constructor != Universe::None){
        Interpreter::getInstance()->call_virtual(constructor,args);
    }
    return new_instance;
}