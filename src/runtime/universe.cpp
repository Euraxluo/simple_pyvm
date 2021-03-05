//
// Created by euraxluo on 2021/1/4.
//
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
}

void Universe::destroy() {
}