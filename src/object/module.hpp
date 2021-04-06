//
// Created by euraxluo on 2021/4/1.
//

#ifndef SIMPLE_PYVM_MODULE_HPP
#define SIMPLE_PYVM_MODULE_HPP

#include <object/string.hpp>

class Object;
class ModuleKlass : public Klass{
private:
    static ModuleKlass* _instance;
    ModuleKlass(){};
public:
    static ModuleKlass* getInstance();
    void initialize();
};
class Module : public Object {
private:
    String* _mod_name;
public:
     Module(Map* x);
     static Module* import_module(Object* mod_name);
     void put(Object* x,Object* y);
     Object* get(Object* x,Object* defaultv = nullptr);
     void extend(Module* mod);

};


#endif //SIMPLE_PYVM_MODULE_HPP
