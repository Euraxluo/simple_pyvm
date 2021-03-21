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
#define STI(x) StringTable::getInstance()->STR(x)
#define STR(x) x##_str

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


Object* Klass::find_and_call(Object *lhs, ArrayList<Object *> *args, Object *func_name,Object *defaultv=nullptr) {
    Object* func = lhs->getattr(func_name);
    if (func != Universe::None){
        if(!args){
            args = new ArrayList<Object*>();
        }
        return Interpreter::getInstance()->call_virtual(func,args);
    }
    if (defaultv != nullptr){
        return defaultv;
    }
    //错误处理
    printf("class ");
    lhs->klass()->name()->print();
    printf(" Error : unsupport operation for class ");
    assert(false);
    return Universe::None;

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

Object* Klass::add(Object *x, Object *y) {
    ObjectArr args = new ArrayList<Object*>();
    args->push(y);
    return find_and_call(x,args,STI(add));
}

Object* Klass::sub(Object *x, Object *y){
    ObjectArr args = new ArrayList<Object*>();
    args->push(y);
    return find_and_call(x,args,STI(sub));
}
Object* Klass::mul(Object *x, Object *y){
    ObjectArr args = new ArrayList<Object*>();
    args->push(y);
    return find_and_call(x,args,STI(mul));
}

Object* Klass::div(Object *x, Object *y){
    ObjectArr args = new ArrayList<Object*>();
    args->push(y);
    return find_and_call(x,args,STI(div));
}

Object* Klass::greater(Object *x, Object *y){
    ObjectArr args = new ArrayList<Object*>();
    args->push(y);
    Object * defaultv = Universe::Inveracious;
    if (compare_klass(x->klass(),y->klass()) >= 0){
        defaultv = Universe::Real;
    }
    return find_and_call(x,args,STI(gt),defaultv);
}


Object* Klass::less(Object *x, Object *y){
    ObjectArr args = new ArrayList<Object*>();
    args->push(y);
    Object * defaultv = Universe::Inveracious;
    if (compare_klass(x->klass(),y->klass()) < 0){
        defaultv = Universe::Real;
    }
    return find_and_call(x,args,STI(lt),defaultv);
}

Object* Klass::equal(Object *x, Object *y){
    ObjectArr args = new ArrayList<Object*>();
    args->push(y);
    Object * defaultv = Universe::Inveracious;
    if (compare_klass(x->klass(),y->klass()) == 0){
        defaultv = Universe::Real;
    }
    return find_and_call(x,args,STI(eq),defaultv);
}

Object* Klass::not_equal(Object *x, Object *y){
    ObjectArr args = new ArrayList<Object*>();
    args->push(y);
    Object * defaultv = Universe::Inveracious;
    if (compare_klass(x->klass(),y->klass()) != 0){
        defaultv = Universe::Real;
    }
    return find_and_call(x,args,STI(ne),defaultv);
}
Object* Klass::ge(Object *x, Object *y){
    ObjectArr args = new ArrayList<Object*>();
    args->push(y);
    Object * defaultv = Universe::Inveracious;
    if (compare_klass(x->klass(),y->klass()) >= 0){
        defaultv = Universe::Real;
    }
    return find_and_call(x,args,STI(ge),defaultv);
}

Object* Klass::le(Object *x, Object *y){
    ObjectArr args = new ArrayList<Object*>();
    args->push(y);
    Object * defaultv = Universe::Inveracious;
    if (compare_klass(x->klass(),y->klass()) <= 0){
        defaultv = Universe::Real;
    }
    return find_and_call(x,args,STI(le),defaultv);
}


Object* Klass::len(Object *x) {
    return find_and_call(x, nullptr,STI(len));
}

Object* Klass::abs(Object *x) {
    return find_and_call(x, nullptr,STI(abs));
}

Object* Klass::pow(Object *x,Object *y) {
    ObjectArr args = new ArrayList<Object*>();
    args->push(y);
    return find_and_call(x, args,STI(pow));
}

Object* Klass::complex(Object *x) {
    return find_and_call(x, nullptr,STI(complex));
}

Object* Klass::int_func(Object *x) {
    return find_and_call(x, nullptr,StringTable::getInstance()->int_str);
}

Object* Klass::float_func(Object *x) {
    return find_and_call(x, nullptr,StringTable::getInstance()->float_str);
}

Object* Klass::hex(Object *x) {
    return find_and_call(x, nullptr,STI(hex));
}

Object* Klass::oct(Object *x) {
    return find_and_call(x, nullptr,STI(oct));
}

Object* Klass::hash_func(Object *x) {
    return find_and_call(x, nullptr,STI(hash));
}

void Klass::store_subscr(Object *x, Object *y,Object *z) {
    ObjectArr args = new ArrayList<Object*>();
    args->push(y);
    args->push(z);
    find_and_call(x,args,STI(setitem));
}


Object* Klass::subscr(Object *x, Object *y) {
    ObjectArr args = new ArrayList<Object*>();
    args->push(y);
    return find_and_call(x,args,STI(getitem));
}

//attrs

Object* Klass::allocate_instance(Object* callable,ArrayList<Object *> *args) {
    Object* new_instance = new Object();
    new_instance->setKlass(((Type*)callable)->sign());
    //找这个class的__init__函数
    //todo:
    Object* constructor = new_instance->klass()->klass_dict()->get(STI(init),Universe::None);
//    Object* constructor = new_instance->getattr(StringTable::getInstance()->init_str);
    if (constructor != Universe::None){
        if (CheckKlass::isFunction(constructor)) {
            constructor = new Method((Function*)constructor, new_instance);
        }
        Interpreter::getInstance()->call_virtual(constructor,args);
    }
    return new_instance;
}

Object* Klass::getattr(Object *x, Object *y) {

    Object* attr = Universe::None;

    if (x->obj_dict() != nullptr){
        attr = x->obj_dict()->get(y,Universe::None);
        if(attr!=Universe::None)
            return attr;
    }

    attr = x->klass()->klass_dict()->get(y,Universe::None);
    if (attr == Universe::None){
        Object* func = x->klass()->klass_dict()->get(STI(getattr),Universe::None);
        if (func->klass() == FunctionKlass::getInstance()){
            func = new Method((Function*)func,x);
            ObjectArr args = new ArrayList<Object*>();
            args->push(y);
            return Interpreter::getInstance()->call_virtual(func,args);
        }
        return attr;
    }


    // Only klass attribute needs bind.
    if (CheckKlass::isFunction(attr)) {
        attr = new Method((Function*)attr, x);
    }
    return attr;
}

Object* Klass::setattr(Object *x, Object *y, Object *z) {
    Object* func  = x->klass()->klass_dict()->get(STI(setattr),Universe::None);
    if (func->klass() == FunctionKlass::getInstance()){
        func = new Method((Function*)func,x);
        ObjectArr args = new ArrayList<Object*>();
        args->push(y);
        args->push(z);
        return Interpreter::getInstance()->call_virtual(func,args);
    }

    if(x->klass() == TypeKlass::getInstance()){
        Type* type_obj = (Type*) x;
        type_obj->sign()->klass_dict()->put(y,z);
        return Universe::None;
    }
    if (!x->obj_dict())
        x->set_obj_dict(new Map());
    x->obj_dict()->put(y,z);
    return Universe::None;
}

//Object* Klass::find_in_parents(Object*x,Object*y){
//    Object* result = Universe::None;
//    result = x->klass()->klass_dict()->get(y,Universe::None);
//    if (result != Universe::None){
//        return result;
//    }
////    if (x->klass())
//    f
//}
