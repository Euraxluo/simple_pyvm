//
// Created by euraxluo on 2020/11/24.
//

#ifndef _OBJECT_HPP
#define _OBJECT_HPP


class Object {
public:
    virtual const char* toString(){}
    virtual unsigned int hashCode(){};
    
    virtual void print(){}
    virtual Object* add(Object* x){}
    virtual Object* i_add(Object* x){}

    virtual Object* greater  (Object* x) {};
    virtual Object* less     (Object* x) {};
    virtual Object* equal    (Object* x) {};
    virtual Object* not_equal(Object* x) {};
    virtual Object* ge       (Object* x) {};
    virtual Object* le       (Object* x) {};
};


#endif //_OBJECT_HPP
