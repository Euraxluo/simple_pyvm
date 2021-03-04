//
// Created by euraxluo on 2021/3/2.
//

#include "list.hpp"
#include "integer.hpp"
#include "string.hpp"
#include "runtime/universe.hpp"
#include "function.hpp"

//ListKlass
ListKlass *ListKlass::_instance = nullptr;

ListKlass *ListKlass::getInstance() {
    if (_instance == nullptr) {
        _instance = new ListKlass();
    }
    return _instance;
}

ListKlass::ListKlass() {
    Dict *klass_dict = new Dict();
    klass_dict->put(new String("append"), new Function(list_append));
    klass_dict->put(new String("insert"), new Function(list_insert));
    klass_dict->put(new String("index"), new Function(list_index));
    set_klass_dict(klass_dict);
}

Object *list_append(ArrayList<Object *> *args) {
    ((List *) (args->get(0)))->append(args->get(1));
    return Universe::None;
}

Object *list_insert(ArrayList<Object *> *args) {
    ((List *) (args->get(0)))->insert(args->get(1), args->get(2));
    return Universe::None;
}

Object *list_index(ArrayList<Object *> *args) {
    List *list = (List *) (args->get(0));
    Object *target = (Object *) (args->get(1));

    int start = 0;
    int end = list->list()->size();
    if (args->size() > 2) {
        start = ((Integer *) (args->get(2)))->value();
    }

    if (args->size() > 3) {
        end = ((Integer *) (args->get(3)))->value();
    }


    assert(list && list->klass() == ListKlass::getInstance());

    for (int i = start; i < end; ++i) {
        if (list->get(i)->equal(target) == Universe::Real) {
            return new Integer(i);
        }
    }
    return Universe::Inveracious;
}


void ListKlass::print(Object *x) {
    List *lx = (List *) x;
    assert(lx && lx->klass() == (Klass *) this);

    printf("[");

    int size = lx->list()->size();
    if (size >= 1) {
        Object *obj = lx->list()->get(0);
        if (obj->klass() == StringKlass::getInstance()) {
            printf("'");
            obj->print();
            printf("'");
        } else {
            obj->print();
        }

    }

    for (int i = 1; i < size; i++) {
        printf(", ");
        Object *obj = lx->list()->get(i);
        if (obj->klass() == StringKlass::getInstance()) {
            printf("'");
            obj->print();
            printf("'");
        } else {
            obj->print();
        }

    }
    printf("]");
}

Object *ListKlass::subscr(Object *x, Object *y) {
    assert(x && x->klass() == (Klass *) this);
    assert(y && y->klass() == (Klass *) IntegerKlass::getInstance());

    List *lx = (List *) x;
    Integer *iy = (Integer *) y;

    return lx->list()->get(iy->value());
}

void ListKlass::store_subscr(Object *x, Object *y, Object *z) {
    assert(x && x->klass() == (Klass *) this);
    assert(y && y->klass() == (Klass *) IntegerKlass::getInstance());

    List *lx = (List *) x;
    Integer *iy = (Integer *) y;

    return lx->list()->set(iy->value(), z);
}

Object *ListKlass::contains(Object *x, Object *y) {
    List *lx = (List *) x;
    assert(lx && lx->klass() == (Klass *) this);

    int size = lx->list()->size();
    for (int i = 0; i < size; i++) {
        if (lx->list()->get(i)->equal(y) == Universe::Real)
            return Universe::Real;
    }

    return Universe::Inveracious;
}

Object *ListKlass::not_contains(Object *x, Object *y) {
    if (contains(x, y) == Universe::Real) {
        return Universe::Inveracious;
    } else {
        return Universe::Real;
    }
}


Object *ListKlass::iter(Object *x) {
    return Universe::None;
}

//List
List::List() {
    setKlass(ListKlass::getInstance());
    _list = new ArrayList<Object *>();
}

List::List(ArrayList<Object *> *objs) {
    setKlass(ListKlass::getInstance());
    _list = objs;
}
