//
// Created by euraxluo on 2021/3/7.
//

#include <runtime/stringTable.hpp>
#include "map.hpp"
#include "integer.hpp"
#include "string.hpp"
#include "runtime/universe.hpp"
#include "function.hpp"
#include "list.hpp"
#include "type.hpp"

//MapKlass
MapKlass *MapKlass::_instance = nullptr;

MapKlass *MapKlass::getInstance() {
    if (_instance == nullptr) {
        _instance = new MapKlass();
    }
    return _instance;
}

MapKlass::MapKlass() {

}

void MapKlass::initialize(){
    Map *klass_dict = new Map();
    klass_dict->put(new String("setdefault"), new Function(map_set_default));
    klass_dict->put(new String("remove"), new Function(map_remove));
    klass_dict->put(new String("keys"), new Function(map_keys));
    klass_dict->put(new String("values"), new Function(map_values));
    klass_dict->put(new String("items"), new Function(map_items));
    klass_dict->put(new String("iterkeys"), new Function(map_iterkeys));
    klass_dict->put(new String("itervalues"), new Function(map_itervalues));
    klass_dict->put(new String("iteritems"), new Function(map_iteritems));
    set_klass_dict(klass_dict);
    (new Type())->setSign(this);
    setName(new String("map"));
    setSuper(ObjectKlass::getInstance());
}


Object *map_set_default(ArrayList<Object *> *args) {
    Map *map = (Map *) (args->get(0));
    Object *key = (Object *) (args->get(1));
    Object *value = (Object *) (args->get(2));
    if (! map->hash_key(key))
        map->put(key,value);
    return Universe::None;
}

Object *map_remove(ArrayList<Object *> *args) {
    Map *map = (Map *) (args->get(0));
    Object *key = (Object *) (args->get(1));
    map->remove(key);
    return Universe::None;
}
Object *map_keys(ArrayList<Object *> *args) {
    Map *map = (Map *) (args->get(0));
    auto tmp = map->map()->MapEntries();
    List *collection = new List();
    while (tmp){
        collection->append(tmp->entry->_k);
        tmp = tmp->nextEntryNode;
    }
    return collection;
}

Object *map_values(ArrayList<Object *> *args) {
    Map *map = (Map *) (args->get(0));
    auto tmp = map->map()->MapEntries();
    List *collection = new List();
    while (tmp){
        collection->append(tmp->entry->_v);
        tmp = tmp->nextEntryNode;
    }
    return collection;
}

Object *map_items(ArrayList<Object *> *args) {
    Map *map = (Map *) (args->get(0));
    auto tmp = map->map()->MapEntries();
    List *items = new List();
    while (tmp){
        List* item = new List();
        item->append(tmp->entry->_k);
        item->append(tmp->entry->_v);
        items->append(item);
        tmp = tmp->nextEntryNode;
    }
    return items;
}

Object *map_iterkeys(ArrayList<Object *> *args) {
    Map *map = (Map *) (args->get(0));
    Object* map_iter = new MapIterator(map);
    map_iter->setKlass(MapIteratorKlass<ITER_KEY>::getInstance());
    return map_iter;
}


Object *map_itervalues(ArrayList<Object *> *args) {
    Map *map = (Map *) (args->get(0));
    Object* map_iter = new MapIterator(map);
    map_iter->setKlass(MapIteratorKlass<ITER_VALUE>::getInstance());
    return map_iter;
}


Object *map_iteritems(ArrayList<Object *> *args) {
    Map *map = (Map *) (args->get(0));
    Object* map_iter = new MapIterator(map);
    map_iter->setKlass(MapIteratorKlass<ITER_ITEM>::getInstance());
    return map_iter;
}


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
        if (cur->entry->_k->klass() == StringKlass::getInstance()) {
            printf("'");
            cur->entry->_k->print();
            printf("'");
        } else {
            cur->entry->_k->print();
        }
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
        if (cur->entry->_k->klass() == StringKlass::getInstance()) {
            printf("'");
            cur->entry->_k->print();
            printf("'");
        } else {
            cur->entry->_k->print();
        }

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
    assert(x && x->klass() == (Klass *) this);
    return ((Map *) x)->remove(y);
}

Object *MapKlass::contains(Object *x, Object *y) {
    Map *mx = (Map *) x;
    assert(mx && mx->klass() == (Klass *) this);
    if (mx->hash_key(y)){
        return Universe::Real;
    }
    return Universe::Inveracious;
}

Object *MapKlass::not_contains(Object *x, Object *y) {
    if (contains(x, y) == Universe::Real) {
        return Universe::Inveracious;
    } else {
        return Universe::Real;
    }
    return nullptr;
}


Object *MapKlass::iter(Object *x) {
    //此处是调用迭代器，然后我们设置为迭代Key
    assert(x && x->klass() == (Klass *) this);
    Object* iter =new MapIterator((Map*)x);
    iter->setKlass(MapIteratorKlass<ITER_KEY>::getInstance());

    return iter;
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

Object* MapKlass::allocate_instance(Object* callable,ArrayList<Object *> *args) {
    if (!args || args->length() == 0)
        return new Map();
    else
        return nullptr;
}

//MapIteratorKlass
template <ITER_TYPE n>
MapIteratorKlass<n> *MapIteratorKlass<n>::_instance = nullptr;

template <ITER_TYPE n>
MapIteratorKlass<n> *MapIteratorKlass<n>::getInstance() {
    if (_instance == nullptr) {
        _instance = new MapIteratorKlass<n>();
    }
    return _instance;
}

template <ITER_TYPE n>
MapIteratorKlass<n>::MapIteratorKlass() {
    const char * klass_name[] = {
            "map-keyiterator",
            "map-valueiterator",
            "map-itemiterator",
    };
    //初始化时设置iter的类型
    setName(new String(klass_name[n]));//set not equal name
    Map* klass_dict = new Map();
    //将next放到klass dict属性中，对应的是mapiterator_next
    klass_dict->put(StringTable::getInstance()->next_str,new Function(mapiterator_next<n>));
    set_klass_dict(klass_dict);

}
template <ITER_TYPE iter_type>
Object *mapiterator_next(ArrayList<Object *> *args) {
    MapIterator * iter = (MapIterator*)(args->get(0));

    int iter_cnt = iter->iter_cnt();
    if (iter_cnt <  iter->owner()->size()) {

        Object *obj ;
        if (iter_type == ITER_KEY){
            obj = iter->keys()->get(iter_cnt);
        } else if (iter_type == ITER_VALUE){
            obj = iter->values()->get(iter_cnt);
        }else if (iter_type == ITER_ITEM){
            obj = iter->items()->get(iter_cnt);
        }
        iter->inc_cnt();
        return obj;
    } else // TODO :StopIteration 异常
        return nullptr;
}


//MapIterator
MapIterator::MapIterator(Map* map){
    _owner = map;
    _iter_cnt = 0;
    // 下面这一行在不同的迭代函数中new的对象不同
//    setKlass(MapIteratorKlass<>::getInstance());
}


//辅助函数，帮助统一入口，但是返回不同的可迭代对象
List* MapIterator::keys(){
    auto tmp = _owner->map()->MapEntries();
    List *keys = new List();
    while (tmp){
        keys->append(tmp->entry->_k);
        tmp = tmp->nextEntryNode;
    }
    return keys;
};
List* MapIterator::values(){
    auto tmp = _owner->map()->MapEntries();
    List *values = new List();
    while (tmp){
        values->append(tmp->entry->_v);
        tmp = tmp->nextEntryNode;
    }
    return values;
};
List* MapIterator::items(){
    auto tmp = _owner->map()->MapEntries();
    List *items = new List();
    while (tmp){
        List* item = new List();
        item->append(tmp->entry->_k);
        item->append(tmp->entry->_v);
        items->append(item);
        tmp = tmp->nextEntryNode;
    }
    return items;
};

//Map
Map::Map() {
    setKlass(MapKlass::getInstance());
    _map = new HashMap<Object*,Object*>();
}

Map::Map(HashMap<Object *,Object*> *objs) {
    setKlass(MapKlass::getInstance());
    _map = objs;
}