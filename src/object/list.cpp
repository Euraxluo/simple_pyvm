//
// Created by euraxluo on 2021/3/2.
//

#include "list.hpp"
#include "integer.hpp"
#include "string.hpp"
#include "runtime/universe.hpp"
#include "function.hpp"

//ListKlass
ListKlass* ListKlass::_instance= nullptr;

ListKlass* ListKlass::getInstance() {
    if (_instance== nullptr){
        _instance = new ListKlass();
    }
    return _instance;
}

ListKlass::ListKlass() {
    Dict* klass_dict = new Dict();
    klass_dict->put(new String("append"),new Function(list_append));
    set_klass_dict(klass_dict);
}

Object* list_append(ArrayList<Object*>* args) {
    ((List*)(args->get(0)))->append(args->get(1));
    return Universe::None;
}

void ListKlass::print(Object* x) {
    List * lx = (List*)x;
    assert(lx && lx->klass() == (Klass*) this);

    printf("[");

    int size = lx->list()->size();
    if (size >= 1){
        Object* obj = lx->list()->get(0);
        if (obj->klass()==StringKlass::getInstance()){
            printf("'");
            obj->print();
            printf("'");
        } else{
            obj->print();
        }

    }

    for (int i = 1; i < size; i++) {
        printf(", ");
        Object* obj = lx->list()->get(i);
        if (obj->klass()==StringKlass::getInstance()){
            printf("'");
            obj->print();
            printf("'");
        } else{
            obj->print();
        }

    }
    printf("]");
}

Object* ListKlass::subscr(Object* x, Object* y) {
    assert(x && x->klass() == (Klass*) this);
    assert(y && y->klass() == (Klass*) IntegerKlass::getInstance());

    List * lx = (List*)x;
    Integer* iy = (Integer*)y;

    return lx->list()->get(iy->value());
}

Object* ListKlass::iter(Object* x) {
    return Universe::None;
}

//List
List::List() {
    setKlass(ListKlass::getInstance());
    _list = new ArrayList<Object*>();
}
List::List(ArrayList<Object*>* objs) {
    setKlass(ListKlass::getInstance());
    _list = objs;
}