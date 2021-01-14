//
// Created by euraxluo on 2021/1/4.
//

#ifndef SIMPLE_PYVM_INTERPRETER_HPP
#define SIMPLE_PYVM_INTERPRETER_HPP

#include <util/hashMap.hpp>
#include "util/arrayList.hpp"
#include "object/object.hpp"
#include "code/codeObject.hpp"
#include "code/bytecode.hpp"
#include "object/integer.hpp"
#include "universe.hpp"

class Block{
public:
    unsigned char _type;//类型，字节码即可
    unsigned int _target;//跳转的目标地址
    int _level;//进入一个Block时，操作数栈深度
    Block():_type(0),_target(0),_level(0){}
    Block(const Block& b): _type(b._type),_target(b._target),_level(b._level){}
    Block(unsigned char type,unsigned int target,int level):
            _type(type),
            _target(target),
            _level(level) {}

};

class Interpreter {
private:
    ArrayList<Object *> *_stack;
    ArrayList<Object *> *_consts;
    ArrayList<Block*> *_loop_stack;

    template<typename T>
    inline void PUSH(const T &x) {
        _stack->push((x));
    }

    inline Object *POP() {
        return _stack->pop();
    }

    inline int STACK_LEVEL() {
        return _stack->size();
    }

public:
    Interpreter() {}

    void run(CodeObject *co) {
        int ptr_c = 0;//程序计数器
        auto code_length = co->_bytecodes->length();//获取字节码长度
        _stack = new ArrayList<Object *>(co->_stack_size);
        _consts = co->_consts;
        _loop_stack = new ArrayList<Block*>();

        ArrayList<Object*>* names = co->_names;
        HashMap<Object*,Object*>* locals = new  HashMap<Object*,Object*>();

        Block* loopBlock;
        while (ptr_c < code_length) {
            auto option_code = Helper::byte2int(co->_bytecodes->c_str()[ptr_c++]);//获取当前操作码
            bool has_argument = option_code >= ByteCode::HAVE_ARGUMENT;//判断是否有参数
            int option_arg = -1;
            if (has_argument) {
                int arg_index = Helper::byte2int(co->_bytecodes->c_str()[ptr_c++]);
                int null_v = Helper::byte2int(co->_bytecodes->c_str()[ptr_c++]);
                auto tmp = null_v << 8;//左移8位
                option_arg = null_v | arg_index;
            }
            Integer *lhs, *rhs;
            Object *v, *w, *u, *attr;

            switch (option_code) {
                case ByteCode::LOAD_CONST:
                    PUSH(_consts->get(option_arg));
                    break;
                case ByteCode::PRINT_ITEM:
                    v = POP();
                    v->print();
                    break;
                case ByteCode::PRINT_NEWLINE:
                    printf("\n");
                    break;
                case ByteCode::BINARY_ADD:
                    v = POP();
                    w = POP();
                    PUSH(w->add(v));
                    break;
                case ByteCode::INPLACE_ADD:
                    v=POP();
                    w=POP();
                    PUSH(w->i_add(v));
                    break;
                case ByteCode::RETURN_VALUE:
                    POP();
                    break;
                case ByteCode::POP_JUMP_IF_FALSE:
                    //如果栈顶元素是0，那么将程序计数器跳转到该指令的参数处
                    v = POP();
                    if (v == Universe::Inveracious) {
                        ptr_c = option_arg;
                    }
                    break;
                case ByteCode::JUMP_FORWARD:
                    ptr_c += option_arg;
                    break;
                case ByteCode::COMPARE_OP:
                    w = POP();
                    v = POP();
                    switch (option_arg) {
                        case ByteCode::GREATER:
                            PUSH(v->greater(w));
                            break;
                        case ByteCode::LESS:
                            PUSH(v->less(w));
                            break;
                        case ByteCode::EQUAL:
                            PUSH(v->equal(w));
                            break;
                        case ByteCode::NOT_EQUAL:
                            PUSH(v->not_equal(w));
                            break;
                        case ByteCode::GREATER_EQUAL:
                            PUSH(v->ge(w));
                            break;
                        case ByteCode::LESS_EQUAL:
                            PUSH(v->le(w));
                            break;
                        default:
                            printf("Error:Unrecongnized compare op %d\n", option_arg);
                    }
                    break;
                case ByteCode::JUMP_ABSOLUTE://参数就是下一个指令的位置
                    ptr_c = option_arg;
                    break;
                case ByteCode::LOAD_NAME:
                    v = names->get(option_arg);
                    w = locals->get(v);
                    if (w!=Universe::None){
                        PUSH(w);
                        break;
                    }
                    PUSH(Universe::None);
                    break;

                case ByteCode::STORE_NAME:
                    v = names->get(option_arg);
                    locals->put(v,POP());
                    break;

                case ByteCode::SETUP_LOOP:
                    _loop_stack->push(new Block(
                            option_code, ptr_c + option_arg,
                            STACK_LEVEL()));
                    break;
                case ByteCode::POP_BLOCK:
                    loopBlock = _loop_stack->pop();
                    while (STACK_LEVEL() > loopBlock->_level) {
                        POP();
                    }
                    break;
                case ByteCode::BREAK_LOOP:
                    loopBlock = _loop_stack->pop();
                    while (STACK_LEVEL() > loopBlock->_level) {
                        POP();
                    }
                    ptr_c = loopBlock->_target;
                    break;

                default:
                    printf("Error:Unrecongnized byte code %d\n", option_code);
            }


        }
        delete locals;
        delete names;

    }

};


#endif //SIMPLE_PYVM_INTERPRETER_HPP
