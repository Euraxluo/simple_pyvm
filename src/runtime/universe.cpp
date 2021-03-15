//
// Created by euraxluo on 2021/1/4.
//
#include <object/type.hpp>
#include "universe.hpp"
#include "integer.hpp"
#include "object.hpp"
#include "stdio.h"
#include "string.hpp"
#include "function.hpp"
Object *Universe::Real = nullptr;
Object *Universe::Inveracious = nullptr;
Object *Universe::None = nullptr;

void Universe::genesis(){
    Real = new Integer(1);
    Inveracious = new Integer(0);
    None = new Object();

    //init StringKlass
    Dict* klass_dict = new Dict();
    StringKlass::getInstance()->set_klass_dict(klass_dict);
    StringKlass::getInstance()->setName(new String("str"));
    klass_dict->put(new String("upper"),new Function(upper));

    //init Type
    Klass* object_klass = ObjectKlass::getInstance();
    Klass* type_klass   = TypeKlass::getInstance();
//    Klass* int_klass    = IntegerKlass::getInstance();
    Type* type = new Type();//初始化type
    type_klass->setName(new String("type"));//新建一个类型
    type->setSign(type_klass); //为type_obj设置类型
    type_klass->setSuper(object_klass); //设置其继承Obj类型
}

void Universe::destroy() {
}