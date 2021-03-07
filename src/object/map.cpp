//
// Created by euraxluo on 2021/3/7.
//

#include "map.hpp"
#include "integer.hpp"
#include "string.hpp"
#include "runtime/universe.hpp"
#include "function.hpp"

//MapKlass
MapKlass *MapKlass::_instance = nullptr;

MapKlass *MapKlass::getInstance() {
    if (_instance == nullptr) {
        _instance = new MapKlass();
    }
    return _instance;
}

MapKlass::MapKlass() {
    Dict *klass_dict = new Dict();
//    klass_dict->put(new String("remove"), new Function(list_remove));
    set_klass_dict(klass_dict);
    setName(new String("map"));
}


//Object *map_remove(ArrayList<Object *> *args) {
//    Map *map = (Map *) (args->get(0));
//    Object *target = (Object *) (args->get(1));
//    assert(map && map->klass() == MapKlass::getInstance());
//
//    for (int i = 0; i < map->map()->size(); ++i) {
//        if (map->get(i)->equal(target) == Universe::Real) {
//            map->map()->remove(i);
//        }
//    }
//    return Universe::None;
//}


//Object *map_sort(ArrayList<Object *> *args) {
//    List *list = (List *) (args->get(0));
//    assert(list && list->klass() == ListKlass::getInstance());
//
//    //顺序排列
//    qsort(list, 0, list->size() - 1, nullptr);
//    //逆序排列
//    qrsort(list, 0, list->size() - 1, nullptr);
//    return Universe::None;
//}
//
//void qrsort(List *list, int left, int right, void *key) {
//    if (left >= right)
//        return;
//    Object *target = list->list()->get(right);//处于小区域的数据
//    int gt = left;//大于
//    int lt = right;//小于
//    int et = lt - 1;//等于
//    while (et >= gt) {
//        if (key != nullptr) {
//            printf("key != nullptr");
//        } else {
//            if (list->get(et)->less(target) == Universe::Real) {
//                Object *tmp = list->get(lt);
//                list->set(lt--, list->get(et));
//                list->set(et--, tmp);
//            } else if (list->get(et)->equal(target) == Universe::Real) {
//                et--;
//            } else {
//                Object *tmp = list->get(gt);
//                list->set(gt++, list->get(et));
//                list->set(et, tmp);
//            }
//        }
//
//    }
//    qrsort(list, left, gt - 1, key);
//    qrsort(list, lt + 1, right, key);
//}
//
//void qsort(List *list, int left, int right, void *key) {
//    if (left >= right)
//        return;
//    Object *target = list->list()->get(left);
//    int lt = left;//小于
//    int et = lt + 1;//等于
//    int gt = right;//大于
//    while (et <= gt) {
//        if (key != nullptr) {
//            printf("key != nullptr");
//            if (list->get(et)->less(target) == Universe::Real) {
//                Object *tmp = list->get(lt);
//                list->set(lt++, list->get(et));
//                list->set(et++, tmp);
//            } else if (list->get(et)->equal(target)) {
//                et++;
//            } else {
//                Object *tmp = list->get(gt);
//                list->set(gt--, list->get(et));
//                list->set(et, tmp);
//            }
//        } else {
//            if (list->get(et)->less(target) == Universe::Real) {
//                Object *tmp = list->get(lt);
//                list->set(lt++, list->get(et));
//                list->set(et++, tmp);
//            } else if (list->get(et)->equal(target) == Universe::Real) {
//                et++;
//            } else {
//                Object *tmp = list->get(gt);
//                list->set(gt--, list->get(et));
//                list->set(et, tmp);
//            }
//        }
//
//    }
//    qsort(list, left, lt - 1, key);
//    qsort(list, gt + 1, right, key);
//}


void MapKlass::print(Object *x) {
    Map *mx = (Map *) x;
    assert(mx && mx->klass() == (Klass *) this);

    printf("{");
    int size = mx->size();
    EntriesNode<Object*,Object*>* cur =mx->map()->MapEntries();
    if (size >= 1) {
        cur->entry->_k->print();
        printf(":");
        if (cur->entry->_v->klass() == StringKlass::getInstance()) {
            printf("'");
            cur->entry->_v->print();
            printf("'");
        } else {
            cur->entry->_v->print();
        }
        cur = cur->nextEntryNode;
    }

    for (int i = 1; i < size; i++) {
        printf(", ");
        cur->entry->_k->print();
        printf(":");
        if (cur->entry->_v->klass() == StringKlass::getInstance()) {
            printf("'");
            cur->entry->_v->print();
            printf("'");
        } else {
            cur->entry->_v->print();
        }
        cur = cur->nextEntryNode;
    }
    printf("}");

}

Object *MapKlass::less(Object *x, Object *y) {
//    //类型比较
//    if (x->klass() != y->klass()) {
//        if (Klass::compare_klass(x->klass(), y->klass()) < 0)
//            return Universe::Real;
//        else
//            return Universe::Inveracious;
//    }
//
//    //类型校验
//    List *lx = (List *) x;
//    List *ly = (List *) y;
//    assert(lx && lx->klass() == (Klass *) this);
//    assert(ly && ly->klass() == (Klass *) this);
//
//    //遍历比较
//    int len = lx->size() < ly->size() ? lx->size() : ly->size();
//    for (int i = 0; i < len; ++i) {
//        //若x_i<y_i,返回真
//        if (lx->get(i)->less(ly->get(i)) == Universe::Real)
//            return Universe::Real;
//        else if (lx->get(i)->equal(ly->get(i)) != Universe::Real)
//            return Universe::Inveracious;
//    }
//    //如果元素都一样，比较长度，短的更小
//    if (lx->size() < ly->size())
//        return Universe::Real;
    return nullptr;
}

Object *MapKlass::equal(Object *x, Object *y) {
//
//    //类型比较
//    if (x->klass() != y->klass())
//        return Universe::Inveracious;
//
//    //类型校验
//    List *lx = (List *) x;
//    List *ly = (List *) y;
//    assert(ly && ly->klass() == (Klass *) this);
//    assert(lx && lx->klass() == (Klass *) this);
//
//    //比较长度
//    if (lx->size() != ly->size())
//        return Universe::Inveracious;
//
//    //遍历比较
//    for (int i = 0; i < lx->size(); ++i) {
//        //若x_i  != y_i,返回False
//        if (lx->get(i)->equal(ly->get(i)) == Universe::Inveracious)
//            return Universe::Inveracious;
//    }
//    return Universe::Real;
    return nullptr;
}

Object *MapKlass::subscr(Object *x, Object *y) {
    assert(x && x->klass() == (Klass *) this);
    return ((Map *) x)->get(y);
}

void MapKlass::store_subscr(Object *x, Object *y, Object *z) {
    assert(x && x->klass() == (Klass *) this);
    return ((Map *) x)->put(y,z);
}

void MapKlass::del_subscr(Object *x, Object *y) {
//    assert(x && x->klass() == (Klass *) this);
//    assert(y && y->klass() == (Klass *) IntegerKlass::getInstance());
//
//    List *lx = (List *) x;
//    Integer *iy = (Integer *) y;
//    return lx->list()->remove(iy->value());
    return;
}

Object *MapKlass::contains(Object *x, Object *y) {
//    List *lx = (List *) x;
//    assert(lx && lx->klass() == (Klass *) this);
//
//    int size = lx->list()->size();
//    for (int i = 0; i < size; i++) {
//        if (lx->list()->get(i)->equal(y) == Universe::Real)
//            return Universe::Real;
//    }
//
//    return Universe::Inveracious;
    return nullptr;
}

Object *MapKlass::not_contains(Object *x, Object *y) {
//    if (contains(x, y) == Universe::Real) {
//        return Universe::Inveracious;
//    } else {
//        return Universe::Real;
//    }
    return nullptr;
}


Object *MapKlass::iter(Object *x) {
//    assert(x && x->klass() == (Klass *) this);
//    return new ListIterator((List *) x);
    return nullptr;
}

Object *MapKlass::add(Object *x, Object *y) {
//    //类型校验
//    List *lx = (List *) x;
//    List *ly = (List *) y;
//    assert(ly && ly->klass() == (Klass *) this);
//    assert(lx && lx->klass() == (Klass *) this);
//    List *z = new List();
//    for (int i = 0; i < lx->size(); ++i) {
//        z->list()->set(i,lx->list()->get(i));
//    }
//    for (int i = 0; i < ly->size(); ++i) {
//        z->list()->set(i+lx->list()->size(),lx->list()->get(i));
//    }
//    return z;
    return nullptr;
}

Object *MapKlass::i_add(Object *x, Object *y) {
//    //类型校验
//    List *lx = (List *) x;
//    List *ly = (List *) y;
//    assert(ly && ly->klass() == (Klass *) this);
//    assert(lx && lx->klass() == (Klass *) this);
//    for (int i = 0; i < ly->size(); ++i) {
//        lx->list()->push(lx->list()->get(i));
//    }
//    return lx;
    return nullptr;
}


Object *MapKlass::mul(Object *x, Object *y) {
//    //类型校验
//    List *lx = (List *) x;
//    assert(lx && lx->klass() == (Klass *) this);
//    Integer *iy = (Integer *) y;
//    assert(iy && iy->klass() == IntegerKlass::getInstance());
//
//    List *z = new List();
//
//    for (int i = 0; i < iy->value(); ++i) {
//        for (int j = 0; j < lx->size(); ++j) {
//            z->list()->set(i*lx->size()+j,lx->list()->get(j));
//        }
//    }
//    return z;
    return nullptr;
}


//MapIteratorKlass
MapIteratorKlass *MapIteratorKlass::_instance = nullptr;

//Object *mapiterator_next(HashMap<Object*,Object*> *map) {
////    MapIterator *iter = (MapIterator *) (args->get(0));
//////    Map *amap = iter->owner();
//////    int iter_cnt = iter->iter_cnt();
//////    if (iter_cnt < amap->map()->size()) {
//////        Object *obj = amap->get(iter_cnt);
//////        iter->inc_cnt();
//////        return obj;
//////    } else // TODO :StopIteration 异常
//        return nullptr;
//}

MapIteratorKlass::MapIteratorKlass() {
    Dict *klass_dict = new Dict();
//    klass_dict->put(new String("next"), new Function(mapiterator_next));
    set_klass_dict(klass_dict);
}

MapIteratorKlass *MapIteratorKlass::getInstance() {
    if (_instance == nullptr) {
        _instance = new MapIteratorKlass();
    }
    return _instance;
}

//MapIterator
MapIterator::MapIterator(Map* map){
    _owner = map;
    _iter_cnt = 0;
    setKlass(MapIteratorKlass::getInstance());
}

//List
Map::Map() {
    setKlass(MapKlass::getInstance());
    _map = new HashMap<Object*,Object*>();
}

Map::Map(HashMap<Object *,Object*> *objs) {
    setKlass(MapKlass::getInstance());
    _map = objs;
}