//
// Created by euraxluo on 2021/3/7.
//

#ifndef SIMPLE_PYVM_MAP_HPP
#define SIMPLE_PYVM_MAP_HPP

#include "klass.hpp"
#include "object.hpp"
#include "integer.hpp"

class MapKlass : public Klass {
private:
    MapKlass();

    static MapKlass *_instance;

public:
    static MapKlass *getInstance();

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
};

class MapIteratorKlass : public Klass {
private:
    MapIteratorKlass();
    static MapIteratorKlass *_instance;
public:
    static MapIteratorKlass *getInstance();

};

class Map : public Object {
private:
    HashMap<Object *,Object*> *_map;
public:
    Map();

    Map(HashMap<Object *,Object*> *map);

    HashMap<Object *,Object*> *map() { return _map; }

    void put(Object*k,Object*v){_map->put(k,v);}
    Object* get(Object*k){ return _map->get(k);}
    bool hash_key(Object*k){ return _map->hash_key(k);}
    int size(){return _map->size();}
    void remove(Object*k){ return _map->remove(k);}

};

class MapIterator : public Object {
private:
    Map *_owner;
    int _iter_cnt;
public:
    MapIterator(Map *owner);

    Map *owner() { return _owner; }

    int iter_cnt() { return _iter_cnt; }

    void inc_cnt() { _iter_cnt++; }
};


#endif //SIMPLE_PYVM_MAP_HPP
