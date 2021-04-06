//
// Created by euraxluo on 2021/1/15.
//

#ifndef SIMPLE_PYVM_KLASS_HPP
#define SIMPLE_PYVM_KLASS_HPP

#include "util/arrayList.hpp"
#include "util/hashMap.hpp"
//#include "map.hpp"

class Object;
class String;
class Type;
class Map;
typedef HashMap<Object *, Object *> Dict;

class Klass {
private:
    String *_name = nullptr;
    Klass *_super = nullptr;
    Type* _type = nullptr;
    ArrayList<Klass*>* _super_list = nullptr;//todo:1.添加一个superList,用来支持mro
    ArrayList<Type*>* _mro = nullptr;//todo:3.添加mro

    //用于记录某一种类型上的属性和方法
    Map *_klass_dict = nullptr;

public:

    Klass() {};
    void initialize(){};
    void set_super_list(ArrayList<Klass*>* super_list){
        _super_list = super_list;
    }
    void setName(String *name) { _name = name; }

    void setSuper(Klass *super) {
        _super = super;
        //todo:2.修改setSuper方法
        if (_super == nullptr){
            return;
        }
        if (_super_list == nullptr){
            _super_list = new ArrayList<Klass*>();
        }
        _super_list->push(super);
    }
    //todo:4.返回mro
    ArrayList<Type*>* mro(){ return _mro;}
    void order_supers();
    void setType(Type* type){_type = type;}


    String *name() { return _name; }

    Klass *super() { return _super; }

    Type* type(){ return _type;}

    virtual void print(Object *obj);

    void set_klass_dict(Map *dict) { _klass_dict = dict; }

    Map *klass_dict() { return _klass_dict; }

    static int compare_klass(Klass * x,Klass * y);
    Object* find_and_call(Object* lhs, ArrayList<Object*>* args, Object* func_name,Object *defaultv);


    //类型支持函数虚拟声明
    virtual Object *greater(Object *x, Object *y);

    virtual Object *less(Object *x, Object *y);

    virtual Object *equal(Object *x, Object *y);

    virtual Object *not_equal(Object *x, Object *y);

    virtual Object *ge(Object *x, Object *y);

    virtual Object *le(Object *x, Object *y);
    virtual Object *contains(Object *x, Object *y) { return 0; };
    virtual Object *not_contains(Object *x, Object *y) { return 0; };


    virtual Object *add(Object *x, Object *y);

    virtual Object *i_add(Object *x, Object *y) { return 0; };

    virtual Object *sub(Object *x, Object *y);

    virtual Object *mul(Object *x, Object *y);

    virtual Object *div(Object *x, Object *y);

    virtual Object *mod(Object *x, Object *y) { return 0; };

    //native func define
    virtual Object *call(ArrayList<Object *> *args) { return 0; }
    virtual Object *allocate_instance(Object* callable,ArrayList<Object*>* args);

    virtual Object *iter(Object*args) { return 0; }
    virtual Object *len(Object *x);
    virtual Object *abs(Object *x);
    virtual Object *pow(Object *x,Object* y);
    virtual Object *complex(Object *x);
    virtual Object *int_func(Object *x);
    virtual Object *float_func(Object *x);
    virtual Object *hex(Object *x);
    virtual Object *oct(Object *x);
    virtual Object *hash_func(Object *x);

    //type function
    virtual Object *subscr(Object *x, Object *y);
    virtual void store_subscr(Object *x, Object *y,Object *z);
    virtual Object* getattr  (Object* x, Object* y);
    virtual Object* setattr  (Object* x, Object* y, Object* z);
    virtual void del_subscr(Object *x, Object *y) { return; }
    Object* get_klass_attr(Object *x, Object *y);

    //type class
    static Object *create_klass(Object *w, Object *pObject, Object *u);
    static Object*  find_in_parents(Object* x,Object* y);
};


#endif //SIMPLE_PYVM_KLASS_HPP
