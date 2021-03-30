//
// Created by euraxluo on 2021/1/31.
//

#ifndef SIMPLE_PYVM_FRAMEOBJECT_HPP
#define SIMPLE_PYVM_FRAMEOBJECT_HPP


#include "../object/object.hpp"
#include "../object/function.hpp"
#include "../util/arrayList.hpp"
#include "../util/helper.hpp"
#include "../util/hashMap.hpp"
#include "../code/codeObject.hpp"

class Block {
public:
    unsigned char _type;//类型，字节码即可
    unsigned int _target;//跳转的目标地址
    int _level;//进入一个Block时，操作数栈深度
    Block() : _type(0), _target(0), _level(0) {}

    Block(const Block &b) : _type(b._type), _target(b._target), _level(b._level) {}

    Block(unsigned char type, unsigned int target, int level) :
            _type(type),
            _target(target),
            _level(level) {}

};

class FrameObject {
private:
    List *_stack = nullptr;
    ArrayList<Block *> *_loop_stack = nullptr;


    ArrayList<Object *> *_consts = nullptr;
    ArrayList<Object *> *_names = nullptr;

    Map *_locals = nullptr;
    Map *_globals = nullptr;
    ArrayList<Object *> *_fast_locals = nullptr;
    ArrayList<Object *> *_closure = nullptr;

    CodeObject *_codes = nullptr;
    FrameObject *_sender = nullptr;
    int _ptr_c = 0;//程序计数器
    bool _entry_frame= false;

    inline int byte2int(char byte) {
        return (byte & 0xFF);
    }

public:
    FrameObject(CodeObject *codes) {
        _consts = codes->_consts;
        _names = codes->_names;

        _locals = new Map();

        _globals = _locals;
        _fast_locals = nullptr;
        _closure = nullptr;


        _stack = new List();
        _loop_stack = new ArrayList<Block *>();

        _codes = codes;
        _ptr_c = 0;
        _sender = nullptr;
        _entry_frame = false;


    }
    FrameObject(Function *func, ArrayList<Object *> *args,int option_arg) {
        assert((args&&option_arg!=0)||(args== nullptr&&option_arg==0));

        _codes = func->func_code();
        _consts = _codes->_consts;
        _names = _codes->_names;

        _locals = new Map();
        _globals = func->globals();
        _fast_locals = new ArrayList<Object *>();

        _stack = new List();
        _loop_stack = new ArrayList<Block *>();
        _ptr_c = 0;
        _sender = nullptr;
        _entry_frame = false;

        const  int argcnt = _codes->_argcount;//函数规定的形参
        const int nargs = option_arg &0xff;
        const int nkwargs = option_arg >>8;
        int kwargs_pos = argcnt;


        //处理默认参数，放到_fast_locals中

        if (func->defaults()) {
            int defaults_cnt = func->defaults()->length();
            int arg_cnt = _codes->_argcount;
            while (defaults_cnt--) {
                _fast_locals->set(--arg_cnt, func->defaults()->get(defaults_cnt));
            }
        }
        //处理扩展位置参数
        ArrayList<Object*>* arglist = nullptr;
        //当实际参数大于形式参数,就把不超过的放到_fast_locals中，多出的放到arglist中
        if (argcnt<nargs){
            int i=0;
            for (;i<argcnt;i++){
                _fast_locals->set(i,args->get(i));
            }
            arglist = new ArrayList<Object*>();
            for (;  i< nargs; i++) {
                arglist->push(args->get(i));
            }

        } else{
            for (int i = 0; i < nargs; ++i) {
                _fast_locals->set(i,args->get(i));
            }
        }
        //处理扩展键参数
        HashMap<Object*,Object*>* kwargmap = nullptr;
        for (int j = 0; j < nkwargs; ++j) {
            Object* key = args->get(nargs+j*2);
            Object* val = args->get(nargs+j*2+1);

            int index = -1;
            for (int i = 0; i < _codes->_var_names->size(); ++i) {
                if (_codes->_var_names->get(i)->equal(key) == Universe::Real){
                    index = i;
                }
            }

            if (index >= 0){
                _fast_locals->set(index,val);
            } else{
                if (kwargmap == nullptr){
                    kwargmap = new HashMap<Object*,Object*>();
                }
                kwargmap->put(key,val);
            }
        }
        //扩展位置参数
        if (_codes->_flag & Function::CO_VARARGS){
            if (arglist == nullptr){
                arglist = new ArrayList<Object*>();
            }
            _fast_locals->set(argcnt,new List(arglist));
            kwargs_pos+=1;
        } else{
            if (arglist != nullptr){
                printf("take more extend parameters. \n");
                assert(false);
            }
        }

        if (_codes->_flag & Function::CO_VARKEYWORDS){
            if (kwargmap == nullptr){
                kwargmap = new HashMap<Object*,Object*>();
            }
            _fast_locals->set(kwargs_pos,new Map(kwargmap));
        } else{
            if (kwargmap != nullptr){
                printf("take more extend kwargs parameters. \n");
                assert(false);
            }
        }

        _closure = nullptr;//x90aa0
        //locals+params
        ArrayList<Object*>* cells = _codes->_cell_vars;

        //判断codeobj中有多少cell变量,把他们放到_closure前边
        if (cells && cells->size()>0){
            _closure = new ArrayList<Object*>(); //addr1
            for (int i = 0; i < cells->size(); ++i) {
                _closure->push(nullptr);
            }
        }
        //函数中传进来的cell变量放到closure中
        if (func->closure() && func->closure()->size() > 0) {//addr2
            if (_closure == nullptr)
                _closure = func->closure()->list();//funtion中的这东西是个tuple
            else {
                List* tmpclosure = new List(_closure);
                _closure = (ArrayList<Object*>*)tmpclosure->add(func->closure());
                delete tmpclosure;
            }
        }
    }

    //未实现参数增强
//    FrameObject(Function *func, ArrayList<Object *> *args) {
//        _codes = func->func_code();
//        _consts = _codes->_consts;
//        _names = _codes->_names;
//        _locals = new HashMap<Object *, Object *>();
//        _globals = func->globals();
//        _stack = new List();
//        _loop_stack = new ArrayList<Block *>();
//        _ptr_c = 0;
//        _sender = nullptr;
//
//        _fast_locals = new ArrayList<Object *>();
//        if (func->defaults()) {
//            int defaults_cnt = func->defaults()->length();
//            int arg_cnt = _codes->_argcount;
//            while (defaults_cnt--) {
//                _fast_locals->set(--arg_cnt, func->defaults()->get(defaults_cnt));
//            }
//        }
//        if (args) {
//            for (int i = 0; i < args->size(); ++i) {
//                _fast_locals->set(i, args->get(i));
//            }
//        }
//    }

    FrameObject() {};

    ~FrameObject() {};
public:


    void set_entry_frame(bool x)    { _entry_frame = x; }
    bool is_entry_frame()           { return _entry_frame; }
    bool is_first_frame()           { return _sender == nullptr; }


    Map *globals() { return _globals; }

    void set_sender(FrameObject *f) { _sender = f; }

    FrameObject *sender() { return _sender; }

    bool is_frist_frame() { return _sender == nullptr; }


    void set_pc(int x) { _ptr_c = x; }

    int get_pc() { return _ptr_c; }

    List *stack() { return _stack; }

    ArrayList<Block *> *loop_stack() { return _loop_stack; }

    ArrayList<Object *> *consts() { return _consts; }

    ArrayList<Object *> *names() { return _names; }

    Map *locals() { return _locals; }

    ArrayList<Object *> *fast_locals() { return _fast_locals; }
    ArrayList<Object *> *closure() { return _closure; }

    Object *get_cell_from_parameter(int i) {
        Object* cecll_name = _codes->_cell_vars->get(i);

        int index = -1;
        for (int j = 0; j < _codes->_var_names->size(); ++j) {
            if (_codes->_var_names->get(j)->equal(cecll_name) == Universe::Real){
                index = j;
            }
        }
        return _fast_locals->get(index);
    }

    bool has_more_codes() {
        return _ptr_c < _codes->_bytecodes->length();//获取字节码长度
    }

    unsigned char get_op_code() {
        return _codes->_bytecodes->c_str()[_ptr_c++];//获取当前操作码
    }

    int get_op_arg() {
        int arg_index = byte2int(_codes->_bytecodes->c_str()[_ptr_c++]);
        int null_v = byte2int(_codes->_bytecodes->c_str()[_ptr_c++]);
        auto tmp = null_v << 8;//左移8位
        return tmp | arg_index;
    }


};


#endif //SIMPLE_PYVM_FRAMEOBJECT_HPP
