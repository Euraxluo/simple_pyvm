//
// Created by euraxluo on 2021/3/14.
//

#include <runtime/stringTable.hpp>
#include <runtime/universe.hpp>
#include "type.hpp"
#include "map.hpp"
#include "string.hpp"
TypeKlass *TypeKlass::_instance = nullptr;

void TypeKlass::initialize() {
    set_klass_dict(new Map());
    (new Type())->setSign(this); //为type_obj设置类型
    setName(new String("type"));//新建一个类型
    setSuper(ObjectKlass::getInstance());
}
TypeKlass *TypeKlass::getInstance() {
    if (_instance == nullptr) {
        _instance = new TypeKlass();
    }
    return _instance;
}

void TypeKlass::print(Object* obj){
    assert(obj->klass() == (Klass*) this);
    printf("<type ");
    printf("'");
    Klass * obj_type = ((Type*)obj)->sign();
    Map* attr_dict =  obj_type->klass_dict();
    if (attr_dict){
        Object* mod = attr_dict->get((Object*)StringTable::getInstance()->mod_str,Universe::None);
        if (mod != Universe::None){
            mod->print();
            printf(".");
        }
    }
    obj_type->name()->print();
    printf("'");
    printf(">");
}
Object* TypeKlass::setattr(Object* x,Object* y,Object*z){
    Type* type_obj = (Type*)x;
    type_obj->sign()->klass_dict()->put(y,z);
    return Universe::None;
}


//Type 类型对象
//每一个对象以后会有一个klass，例如list的对象是ListKlass，这个ListKlass会有一个type
//比如ListKlass的type对象是这样的{klass:TypeKlass;own_klass:ListKlass}
Type::Type() {
    setKlass(TypeKlass::getInstance());
}
void Type::setSign(Klass *k) {
    _sign = k;
    k->setType(this);
}
