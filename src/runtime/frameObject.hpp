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
    ArrayList<Object *> *_stack;
    ArrayList<Block *> *_loop_stack;


    ArrayList<Object *> *_consts;
    ArrayList<Object *> *_names;

    HashMap<Object *, Object *> *_locals;
    HashMap<Object *, Object *> *_globals;

    CodeObject *_codes;
    FrameObject *_sender;
    int _ptr_c = 0;//程序计数器
public:
    FrameObject(CodeObject *codes) {
        _consts = codes->_consts;
        _names = codes->_names;

        _locals = new HashMap<Object *, Object *>();
        _globals = _locals;


        _stack = new ArrayList<Object *>();
        _loop_stack = new ArrayList<Block *>();

        _codes = codes;
        _ptr_c = 0;
        _sender = nullptr;
    }

    FrameObject(Function *func) {
        _codes = func->_func_code;
        _consts = _codes->_consts;
        _names = _codes->_names;
        _locals = new HashMap<Object *, Object *>();
        _globals = func->globals();
        _stack = new ArrayList<Object *>();
        _loop_stack = new ArrayList<Block *>();
        _ptr_c = 0;
        _sender = nullptr;

    }

    FrameObject() {};

    ~FrameObject() {};
public:
    HashMap<Object *, Object *>* globals(){ return _globals;}

    void set_sender(FrameObject *f) { _sender = f; }

    FrameObject *sender() { return _sender; }

    bool is_frist_frame() { return _sender == nullptr; }


    void set_pc(int x) { _ptr_c = x; }

    int get_pc() { return _ptr_c; }

    ArrayList<Object *> *stack() { return _stack; }

    ArrayList<Block *> *loop_stack() { return _loop_stack; }

    ArrayList<Object *> *consts() { return _consts; }

    ArrayList<Object *> *names() { return _names; }

    HashMap<Object *, Object *> *locals() { return _locals; }

    bool has_more_codes() {
        return _ptr_c < _codes->_bytecodes->length();//获取字节码长度
    }

    unsigned char get_op_code() {
        return (unsigned char) Helper::byte2int(_codes->_bytecodes->c_str()[_ptr_c++]);//获取当前操作码
    }

    int get_op_arg() {
        int arg_index = Helper::byte2int(_codes->_bytecodes->c_str()[_ptr_c++]);
        int null_v = Helper::byte2int(_codes->_bytecodes->c_str()[_ptr_c++]);
        auto tmp = null_v << 8;//左移8位
        return null_v | arg_index;
    }


};


#endif //SIMPLE_PYVM_FRAMEOBJECT_HPP
