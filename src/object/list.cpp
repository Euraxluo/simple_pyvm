//
// Created by euraxluo on 2021/3/2.
//

#include "list.hpp"
#include "integer.hpp"
#include "string.hpp"
#include "runtime/universe.hpp"
#include "function.hpp"
#include "type.hpp"

//ListKlass
ListKlass *ListKlass::_instance = nullptr;

ListKlass *ListKlass::getInstance() {
    if (_instance == nullptr) {
        _instance = new ListKlass();
    }
    return _instance;
}

void ListKlass::initialize(){
    Map *klass_dict = new Map();
    klass_dict->put(new String("append"), new Function(list_append));
    klass_dict->put(new String("insert"), new Function(list_insert));
    klass_dict->put(new String("index"), new Function(list_index));
    klass_dict->put(new String("pop"), new Function(list_pop));
    klass_dict->put(new String("remove"), new Function(list_remove));
    klass_dict->put(new String("reverse"), new Function(list_reverse));
    klass_dict->put(new String("sort"), new Function(list_sort));
    set_klass_dict(klass_dict);
    (new Type())->setSign(this);
    setName(new String("list"));
    setSuper(ObjectKlass::getInstance());
}

Object *list_append(ArrayList<Object *> *args) {
    ((List *) (args->get(0)))->append(args->get(1));
    return Universe::None;
}

Object *list_insert(ArrayList<Object *> *args) {
    ((List *) (args->get(0)))->insert(args->get(1), args->get(2));
    return Universe::None;
}

Object *list_remove(ArrayList<Object *> *args) {
    List *list = (List *) (args->get(0));
    Object *target = (Object *) (args->get(1));
    assert(list && list->klass() == ListKlass::getInstance());

    for (int i = 0; i < list->list()->size(); ++i) {
        if (list->get(i)->equal(target) == Universe::Real) {
            list->list()->remove(i);
        }
    }
    return Universe::None;
}

Object *list_reverse(ArrayList<Object *> *args) {
    List *list = (List *) (args->get(0));
    assert(list && list->klass() == ListKlass::getInstance());
    int i = 0;
    int j = list->size() - 1;
    while (i < j) {
        Object *tmp = list->get(i);
        list->set(i, list->get(j));
        list->set(j, tmp);
        i++;
        j--;
    }
    return Universe::None;
}

Object *list_sort(ArrayList<Object *> *args) {
    List *list = (List *) (args->get(0));
    assert(list && list->klass() == ListKlass::getInstance());

    //顺序排列
    qsort(list, 0, list->size() - 1, nullptr);
    //逆序排列
    qrsort(list, 0, list->size() - 1, nullptr);
    return Universe::None;
}

void qrsort(List *list, int left, int right, void *key) {
    if (left >= right)
        return;
    Object *target = list->list()->get(right);//处于小区域的数据
    int gt = left;//大于
    int lt = right;//小于
    int et = lt - 1;//等于
    while (et >= gt) {
        if (key != nullptr) {
            printf("key != nullptr");
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
        } else {
            if (list->get(et)->less(target) == Universe::Real) {
                Object *tmp = list->get(lt);
                list->set(lt--, list->get(et));
                list->set(et--, tmp);
            } else if (list->get(et)->equal(target) == Universe::Real) {
                et--;
            } else {
                Object *tmp = list->get(gt);
                list->set(gt++, list->get(et));
                list->set(et, tmp);
            }
        }

    }
    qrsort(list, left, gt - 1, key);
    qrsort(list, lt + 1, right, key);
}

void qsort(List *list, int left, int right, void *key) {
    if (left >= right)
        return;
    Object *target = list->list()->get(left);
    int lt = left;//小于
    int et = lt + 1;//等于
    int gt = right;//大于
    while (et <= gt) {
        if (key != nullptr) {
            printf("key != nullptr");
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
        } else {
            if (list->get(et)->less(target) == Universe::Real) {
                Object *tmp = list->get(lt);
                list->set(lt++, list->get(et));
                list->set(et++, tmp);
            } else if (list->get(et)->equal(target) == Universe::Real) {
                et++;
            } else {
                Object *tmp = list->get(gt);
                list->set(gt--, list->get(et));
                list->set(et, tmp);
            }
        }

    }
    qsort(list, left, lt - 1, key);
    qsort(list, gt + 1, right, key);
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

Object *list_pop(ArrayList<Object *> *args) {
    List *list = (List *) (args->get(0));
    assert(list && list->klass() == ListKlass::getInstance());

    int target = list->list()->size() - 1;
    if (args->size() > 1) {
        target = ((Integer *) (args->get(1)))->value();

    }
    list->list()->remove(target);
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

Object *ListKlass::less(Object *x, Object *y) {
    //类型比较
    if (x->klass() != y->klass()) {
        if (Klass::compare_klass(x->klass(), y->klass()) < 0)
            return Universe::Real;
        else
            return Universe::Inveracious;
    }

    //类型校验
    List *lx = (List *) x;
    List *ly = (List *) y;
    assert(lx && lx->klass() == (Klass *) this);
    assert(ly && ly->klass() == (Klass *) this);

    //遍历比较
    int len = lx->size() < ly->size() ? lx->size() : ly->size();
    for (int i = 0; i < len; ++i) {
        //若x_i<y_i,返回真
        if (lx->get(i)->less(ly->get(i)) == Universe::Real)
            return Universe::Real;
        else if (lx->get(i)->equal(ly->get(i)) != Universe::Real)
            return Universe::Inveracious;
    }
    //如果元素都一样，比较长度，短的更小
    if (lx->size() < ly->size())
        return Universe::Real;
}

Object *ListKlass::equal(Object *x, Object *y) {

    //类型比较
    if (x->klass() != y->klass())
        return Universe::Inveracious;

    //类型校验
    List *lx = (List *) x;
    List *ly = (List *) y;
    assert(ly && ly->klass() == (Klass *) this);
    assert(lx && lx->klass() == (Klass *) this);

    //比较长度
    if (lx->size() != ly->size())
        return Universe::Inveracious;

    //遍历比较
    for (int i = 0; i < lx->size(); ++i) {
        //若x_i  != y_i,返回False
        if (lx->get(i)->equal(ly->get(i)) == Universe::Inveracious)
            return Universe::Inveracious;
    }
    return Universe::Real;
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

void ListKlass::del_subscr(Object *x, Object *y) {
    assert(x && x->klass() == (Klass *) this);
    assert(y && y->klass() == (Klass *) IntegerKlass::getInstance());

    List *lx = (List *) x;
    Integer *iy = (Integer *) y;
    return lx->list()->remove(iy->value());
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
    assert(x && x->klass() == (Klass *) this);
    return new ListIterator((List *) x);
}

Object *ListKlass::add(Object *x, Object *y) {
    //类型校验
    List *lx = (List *) x;
    List *ly = (List *) y;
    assert(ly && ly->klass() == (Klass *) this);
    assert(lx && lx->klass() == (Klass *) this);
    List *z = new List();
    for (int i = 0; i < lx->size(); ++i) {
        z->list()->set(i,lx->list()->get(i));
    }
    for (int i = 0; i < ly->size(); ++i) {
        z->list()->set(i+lx->list()->size(),lx->list()->get(i));
    }
    return z;
}

Object *ListKlass::i_add(Object *x, Object *y) {
    //类型校验
    List *lx = (List *) x;
    List *ly = (List *) y;
    assert(ly && ly->klass() == (Klass *) this);
    assert(lx && lx->klass() == (Klass *) this);
    for (int i = 0; i < ly->size(); ++i) {
        lx->list()->push(lx->list()->get(i));
    }
    return lx;
}


Object *ListKlass::mul(Object *x, Object *y) {
    //类型校验
    List *lx = (List *) x;
    assert(lx && lx->klass() == (Klass *) this);
    Integer *iy = (Integer *) y;
    assert(iy && iy->klass() == IntegerKlass::getInstance());

    List *z = new List();

    for (int i = 0; i < iy->value(); ++i) {
        for (int j = 0; j < lx->size(); ++j) {
            z->list()->set(i*lx->size()+j,lx->list()->get(j));
        }
    }
    return z;
}

//Native Function
Object *ListKlass::len(Object *obj) {
    List *l = (List *) obj;
    assert(l && l->klass() == ListKlass::getInstance());
    return new Integer(l->size());
}


Object* ListKlass::allocate_instance(Object* callable,ArrayList<Object *> *args) {
    if (!args || args->length() == 0)
        return new List();
    else
        return nullptr;
}



//ListIteratorKlass
ListIteratorKlass *ListIteratorKlass::_instance = nullptr;

Object *listiterator_next(ArrayList<Object *> *args) {
    ListIterator *iter = (ListIterator *) (args->get(0));
    List *alist = iter->owner();
    int iter_cnt = iter->iter_cnt();
    if (iter_cnt < alist->list()->size()) {
        Object *obj = alist->get(iter_cnt);
        iter->inc_cnt();
        return obj;
    } else // TODO :StopIteration 异常
        return nullptr;
}

ListIteratorKlass::ListIteratorKlass() {
    Map *klass_dict = new Map();
    klass_dict->put(new String("next"), new Function(listiterator_next));
    set_klass_dict(klass_dict);
}

ListIteratorKlass *ListIteratorKlass::getInstance() {
    if (_instance == nullptr) {
        _instance = new ListIteratorKlass();
    }
    return _instance;
}

//ListIterator
ListIterator::ListIterator(List* list){
    _owner = list;
    _iter_cnt = 0;
    setKlass(ListIteratorKlass::getInstance());
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
