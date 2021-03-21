//
// Created by euraxluo on 2021/3/14.
//

#ifndef SIMPLE_PYVM_TYPE_HPP
#define SIMPLE_PYVM_TYPE_HPP

#include "klass.hpp"
#include "object.hpp"
class TypeKlass : public Klass{
private:
    TypeKlass();
    static TypeKlass* _instance;
public:
    static TypeKlass*getInstance();
    virtual void print(Object* obj);
    virtual Object* setattr(Object* x,Object* y,Object*z);
};


class Type : public Object{
private:
    Klass* _sign;
public:
    Type();
    void setSign(Klass *k);
    Klass* sign(){ return _sign;}
};


#endif //SIMPLE_PYVM_TYPE_HPP
