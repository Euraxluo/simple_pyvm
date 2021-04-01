//
// Created by euraxluo on 2021/1/4.
//
#include <object/type.hpp>
#include <object/method.hpp>
#include <object/cell.hpp>
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
    Real = new String("True");
    Inveracious = new String("False");
    None = new String("None");
    //todo:10.再迁移所有的初始化语句到initialize方法中

    ObjectKlass::getInstance()->initialize();
    TypeKlass::getInstance()->initialize();
    IntegerKlass::getInstance()->initialize();
    StringKlass::getInstance()->initialize();
    ListKlass::getInstance()->initialize();
    MapKlass::getInstance()->initialize();
    FunctionKlass::getInstance()->initialize();
    MethodKlass::getInstance()->initialize();
    NativeFunctionKlass::getInstance()->initialize();
    CellKlass::getInstance()->initialize();


    //todo:9.先把所有类的mro生成成功，然后打印出来
    ObjectKlass::getInstance()->order_supers();
    TypeKlass::getInstance()->order_supers();
    IntegerKlass::getInstance()->order_supers();
    StringKlass::getInstance()->order_supers();
    ListKlass::getInstance()->order_supers();
    MapKlass::getInstance()->order_supers();
    FunctionKlass::getInstance()->order_supers();
    MethodKlass::getInstance()->order_supers();
    NativeFunctionKlass::getInstance()->order_supers();
    CellKlass::getInstance()->order_supers();

}

void Universe::destroy() {
}