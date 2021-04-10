//
// Created by euraxluo on 2021/3/2.
//

#ifndef SIMPLE_PYVM_LIST_HPP
#define SIMPLE_PYVM_LIST_HPP

#include "klass.hpp"
#include "object.hpp"
#include "integer.hpp"

class ListKlass : public Klass {
private:
    ListKlass(){};

    static ListKlass *_instance;

public:
    void initialize();
    static ListKlass *getInstance();

    virtual void print(Object *obj);

    virtual Object *less(Object *x, Object *y);

    virtual Object *equal(Object *x, Object *y);

    virtual Object *subscr(Object *x, Object *y);

    virtual void store_subscr(Object *x, Object *y, Object *z);

    virtual void del_subscr(Object *x, Object *y);

    virtual Object *contains(Object *x, Object *y);

    virtual Object *not_contains(Object *x, Object *y);

    virtual Object *iter(Object *x);

    virtual Object *add(Object *x, Object *y);

    virtual Object *i_add(Object *x, Object *y);

    virtual Object *mul(Object *x, Object *y);

    virtual Object *len(Object *x);

    virtual Object *allocate_instance(Object* callable,ArrayList<Object*>* args);
};

class ListIteratorKlass : public Klass {
private:
    ListIteratorKlass();
    static ListIteratorKlass *_instance;
public:
    static ListIteratorKlass *getInstance();

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

    void insert(Object *idx, Object *obj) { _list->insert(((Integer *) idx)->value(), obj); }

    Object *pop() { return _list->pop(); }

    Object *get(int index) { return _list->get(index); }

    void set(int i, Object *obj) { _list->set(i, obj); }

    Object *top() { return get(-1); }
};

class ListIterator : public Object {
private:
    List *_owner;
    int _iter_cnt;
public:
    ListIterator(List *owner);

    List *owner() { return _owner; }

    int iter_cnt() { return _iter_cnt; }

    void inc_cnt() { _iter_cnt++; }
};


Object *list_append(ArrayList<Object *> *args);

Object *list_insert(ArrayList<Object *> *args);

Object *list_index(ArrayList<Object *> *args);

Object *list_pop(ArrayList<Object *> *args);

Object *list_remove(ArrayList<Object *> *args);

Object *list_reverse(ArrayList<Object *> *args);

Object *list_sort(ArrayList<Object *> *args);

void qsort(List *list, int left, int right, void *key);

void qrsort(List *list, int left, int right, void *key);

#endif //SIMPLE_PYVM_LIST_HPP
