//
// Created by euraxluo on 2021/3/11.
//

#ifndef SIMPLE_PYVM_CELLOBJECT_HPP
#define SIMPLE_PYVM_CELLOBJECT_HPP


#include <object/object.hpp>
#include <util/arrayList.hpp>
#include "object/klass.hpp"

class CellKlass : public Klass{
private:
    CellKlass();
    static CellKlass * _instance;
public:
    static CellKlass* getInstance();
//    virtual void oops_do(OopClosure* closure,Object* obj);
    virtual size_t size();
};

class CellObject  : public Object{
private:
    ArrayList<Object*>* _table;//记录cell变量所在的closure表
    int _index;//记录该变量在表中的序号
public:
    CellObject(ArrayList<Object*>* l,int i);
    Object* value();
};


#endif //SIMPLE_PYVM_CELLOBJECT_HPP
