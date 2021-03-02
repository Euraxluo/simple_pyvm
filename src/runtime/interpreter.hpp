//
// Created by euraxluo on 2021/1/4.
//

#ifndef SIMPLE_PYVM_INTERPRETER_HPP
#define SIMPLE_PYVM_INTERPRETER_HPP

#include <object/method.hpp>
#include <object/checkKlass.hpp>
#include <object/list.hpp>
#include "hashMap.hpp"
#include "object/function.hpp"
#include "util/arrayList.hpp"
#include "object/object.hpp"
#include "code/codeObject.hpp"
#include "code/bytecode.hpp"
#include "object/integer.hpp"
#include "universe.hpp"
#include "frameObject.hpp"

typedef ArrayList<Object *> *ObjectArr;

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

    inline Object *BUILTIN_TRUE() {
        return Universe::Real;
    }

    inline Object *BUILTIN_FALSE() {
        return Universe::Inveracious;
    }

    inline Object *BUILTIN_NONE() {
        return Universe::None;
    }

    HashMap<Object *, Object *> *_builtins;

public:
    Interpreter() {
        _builtins = new HashMap<Object *, Object *>();
        _builtins->put(new String("True"), BUILTIN_TRUE());
        _builtins->put(new String("False"), BUILTIN_FALSE());
        _builtins->put(new String("None"), BUILTIN_NONE());
        _builtins->put(new String("len"), new Function(len)); //native func
    }

    void build_frame(Object *callable, ObjectArr args) {
        if (CheckKlass::isNative(callable)) {//NativeFunctionKlass
            PUSH(((Function *) callable)->call(args));
        } else if (CheckKlass::isMethod(callable)) {//MethodKlass
            Method *method = (Method *) callable;
            if (!args) {
                args = new ArrayList<Object *>(1);
            }
            args->insert(0, method->owner());
            build_frame(method->func(), args);
        } else if (CheckKlass::isFunction(callable)) {//FunctionKlass
            FrameObject *frame = new FrameObject((Function *) callable, args);
            frame->set_sender(_frame);//一个指针，设置调用者的栈桢
            _frame = frame;
        } else {
            printf("Error:Build Frame Faild\n");
        }

    }

    void destroy_frame() {
        //切换栈桢，释放旧栈桢
        auto old_frame = _frame;
        _frame = _frame->sender();
        delete old_frame;

    }

    void leave_frame(Object *ret_value) {
        if (!_frame->sender()) {//如果该栈是最顶层，那么直接退出，否则需要回收该栈
            return;
        }
        destroy_frame();
        PUSH(ret_value);
    }

    void eval_frame() {
        Block *loopBlock;
        ArrayList<Object *> *args = nullptr;
        Function *fo;
        Object *v, *w, *u, *attr;

        while (_frame->has_more_codes()) {
            auto option_code = _frame->get_op_code();
            bool has_argument = option_code >= ByteCode::HAVE_ARGUMENT;//判断是否有参数

            int option_arg = -1;
            if (has_argument) {
                option_arg = _frame->get_op_arg();
            }

            switch (option_code) {
                case ByteCode::POP_TOP:
                    POP();
                    break;
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
                        case ByteCode::IS:
                            PUSH(v->equal(w));
                            break;
                        case ByteCode::IS_NOT:
                            PUSH(v->not_equal(w));
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
                    w = _frame->locals()->get(v, Universe::None);
                    if (w && w != Universe::None) {
                        PUSH(w);
                        break;
                    }
                    w = _frame->globals()->get(v, Universe::None);
                    if (w && w != Universe::None) {
                        PUSH(w);
                        break;
                    }
                    w = _builtins->get(v, Universe::None);
                    if (w && w != Universe::None) {
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
                    fo->set_globals(_frame->globals());//将创建函数时的环境变量传递给函数
                    if (option_arg > 0) {
                        args = new ArrayList<Object *>(option_arg);
                        while (option_arg--) {
                            args->set(option_arg, POP());
                        }
                    }
                    fo->set_default(args);
                    if (args != nullptr) {
                        delete args;
                        args = nullptr;
                    }
                    PUSH(fo);//读取func对象，压入栈内
                    break;
                case ByteCode::CALL_FUNCTION:
                    if (option_arg > 0) {//该字节码的参数是，函数参数个数
                        args = new ArrayList<Object *>(option_arg);
                        while (option_arg--) {
                            args->set(option_arg, POP());
                        }
                    }
                    build_frame(POP(), args);//将栈顶的func对象取出，替换当前栈桢，运行frame内的字节码
                    if (args != nullptr) {
                        delete args;
                        args = nullptr;
                    }
                    break;
                case ByteCode::RETURN_VALUE :
                    leave_frame(POP());
                    if (!_frame)
                        return;//主程序中，直接结束调用
                    break;
                case ByteCode::LOAD_GLOBAL:
                    v = _frame->names()->get(option_arg);
                    w = _frame->globals()->get(v, Universe::None);
                    if (w != Universe::None) {//check
                        PUSH(w);
                        break;
                    }
                    w = _builtins->get(v, Universe::None);
                    if (w != Universe::None) {
                        PUSH(w);
                        break;
                    }
                    PUSH(Universe::None);
                    break;
                case ByteCode::STORE_GLOBAL:
                    v = _frame->names()->get(option_arg);
                    _frame->globals()->put(v, POP());
                    break;
                case ByteCode::LOAD_FAST:
                    PUSH(_frame->fast_locals()->get(option_arg));
                    break;
                case ByteCode::STORE_FAST:
                    _frame->fast_locals()->set(option_arg, POP());
                    break;
                case ByteCode::LOAD_ATTR:
                    v = POP();
                    w = _frame->names()->get(option_arg);
                    PUSH(v->getattr(w));
                    break;
                case ByteCode::BUILD_LIST:
                    v  = new List();
                    while(option_arg--){
                        ((List*)v)->set(option_arg,POP());
                    }
                    PUSH(v);
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
