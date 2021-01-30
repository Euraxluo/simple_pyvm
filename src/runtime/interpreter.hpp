//
// Created by euraxluo on 2021/1/4.
//

#ifndef SIMPLE_PYVM_INTERPRETER_HPP
#define SIMPLE_PYVM_INTERPRETER_HPP

#include <util/hashMap.hpp>
#include <object/function.hpp>
#include "util/arrayList.hpp"
#include "object/object.hpp"
#include "code/codeObject.hpp"
#include "code/bytecode.hpp"
#include "object/integer.hpp"
#include "universe.hpp"
#include "frameObject.hpp"

class Interpreter {
private:

    FrameObject *_frame;

    template<typename T>
    inline void PUSH(const T &x) {
        _frame->stack()->push((x));
    }

    inline Object *POP() {
        return _frame->stack()->pop();
    }

    inline int STACK_LEVEL() {
        return _frame->stack()->size();
    }

public:
    Interpreter() {}

    void build_frame(Object *callable) {
        FrameObject *frame = new FrameObject((Function *) callable);
        frame->set_sender(_frame);//一个指针，设置调用者的栈桢
        _frame = frame;
    }

    void destroy_frame() {
        //切换栈桢，释放旧栈桢
        auto old_frame = _frame;
        _frame = _frame->sender();
        delete old_frame;

    }

    void leave_frame(Object *ret_value) {
        if (!_frame->sender()) {
//            delete _frame;
//            _frame = nullptr;
            return;
        }
        destroy_frame();
        PUSH(ret_value);
    }

    void eval_frame() {
        Block *loopBlock;
        while (_frame->has_more_codes()) {
            auto option_code = _frame->get_op_code();
            bool has_argument = option_code >= ByteCode::HAVE_ARGUMENT;//判断是否有参数
            Function *fo;
            Object *v, *w, *u, *attr;
            int option_arg = -1;
            if (has_argument) {
                option_arg = _frame->get_op_arg();
            }

            switch (option_code) {
                case ByteCode::LOAD_CONST:
                    PUSH(_frame->consts()->get(option_arg));
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
                    v = POP();
                    w = POP();
                    PUSH(w->i_add(v));
                    break;
                case ByteCode::POP_JUMP_IF_FALSE:
                    //如果栈顶元素是0，那么将程序计数器跳转到该指令的参数处
                    v = POP();
                    if (v == Universe::Inveracious) {
                        _frame->set_pc(option_arg);
                    }
                    break;
                case ByteCode::JUMP_FORWARD:
                    _frame->set_pc(_frame->get_pc() + option_arg);
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
                    _frame->set_pc(option_arg);
                    break;
                case ByteCode::LOAD_NAME:
                    v = _frame->names()->get(option_arg);
                    w = _frame->locals()->get(v);
                    if (w != Universe::None) {
                        PUSH(w);
                        break;
                    }
                    PUSH(Universe::None);
                    break;

                case ByteCode::STORE_NAME:
                    v = _frame->names()->get(option_arg);
                    _frame->locals()->put(v, POP());
                    break;

                case ByteCode::SETUP_LOOP:
                    _frame->loop_stack()->push(new Block(
                            option_code, _frame->get_pc() + option_arg,
                            STACK_LEVEL()));
                    break;
                case ByteCode::POP_BLOCK:
                    loopBlock = _frame->loop_stack()->pop();
                    while (STACK_LEVEL() > loopBlock->_level) {
                        POP();
                    }
                    break;
                case ByteCode::BREAK_LOOP:
                    loopBlock = _frame->loop_stack()->pop();
                    while (STACK_LEVEL() > loopBlock->_level) {
                        POP();
                    }
                    _frame->set_pc(loopBlock->_target);
                    break;
                case ByteCode::MAKE_FUNCTION:
                    v = POP();
                    fo = new Function(v);
                    PUSH(fo);//读取func对象，压入栈内
                    break;
                case ByteCode::CALL_FUNCTION:
                    build_frame(POP());//将栈顶的func对象取出，替换当前栈桢，运行frame内的字节码
                    break;
                case ByteCode::RETURN_VALUE :
                    leave_frame(POP());
                    if (!_frame)
                        return;//主程序中，直接结束调用
                    break;
                default:
                    printf("Error:Unrecongnized byte code %d\n", option_code);
            }
        }
    }

    void run(CodeObject *co) {
        _frame = new FrameObject(co);
        eval_frame();
        destroy_frame();

    }

};


#endif //SIMPLE_PYVM_INTERPRETER_HPP
