//
// Created by euraxluo on 2021/3/2.
//

#ifndef SIMPLE_PYVM_LIST_HPP
#define SIMPLE_PYVM_LIST_HPP

#include "klass.hpp"
#include "object.hpp"
class ListKlass : public Klass {
private:
    ListKlass();
    static ListKlass *_instance;

public:
    static ListKlass *getInstance();

    virtual void print(Object *obj);

    virtual Object *subscr(Object *x, Object *y);

    virtual Object *iter(Object *x);
};

class List : public Object {
private:
    ArrayList<Object *> *_list;
public:
    List();

    List(ArrayList<Object *> *objs);

    ArrayList<Object *> *list() { return _list; }

    int size() { return _list->size(); }

    void append(Object *obj) { _list->push(obj); }

    Object *pop() { return _list->pop(); }

    Object *get(int index) { return _list->get(index); }

    void set(int i, Object *obj) { _list->set(i, obj); }

    Object *top() { return get(size() - 1); }
};
Object* list_append(ArrayList<Object*>* args);

#endif //SIMPLE_PYVM_LIST_HPP