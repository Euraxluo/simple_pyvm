//
// Created by euraxluo on 2021/1/4.
//

#ifndef SIMPLE_PYVM_INTERPRETER_HPP
#define SIMPLE_PYVM_INTERPRETER_HPP

#include <object/method.hpp>
#include <object/checkKlass.hpp>
#include <object/list.hpp>
#include <object/map.hpp>
#include "hashMap.hpp"
#include "object/function.hpp"
#include "util/arrayList.hpp"
#include "object/object.hpp"
#include "code/codeObject.hpp"
#include "code/bytecode.hpp"
#include "object/integer.hpp"
#include "universe.hpp"
#include "frameObject.hpp"
#include "stringTable.hpp"
#include "module.hpp"

typedef ArrayList<Object *> *ObjectArr;
class Interpreter {
private:

    FrameObject *_frame= nullptr;
    Module *_builtins;
    Object* _ret_value = nullptr;
    Map* _modules;

    static Interpreter* _instance;

    template<typename T>
    inline void PUSH(const T &x) {
        _frame->stack()->append(x);
    }

    inline Object *POP() {
        return _frame->stack()->pop();
    }

    inline Object *TOP() {
        return _frame->stack()->top();
    }

    inline int STACK_LEVEL() {
        return _frame->stack()->size();
    }

    template<typename T>
    inline Object *PEEK(const T &x) {
        return _frame->stack()->get(x);
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


public:
    static Interpreter* getInstance();
    Interpreter();

    void build_frame(Object *callable, ObjectArr args, int option_arg);

    void destroy_frame();
    void leave_frame();

    void enter_frame(FrameObject* frame);

    void eval_frame();

    void run(CodeObject *co);
    Map* run_mod(CodeObject *co,String* run_mod);
    Object* call_virtual (Object* func,ObjectArr args);
};


#endif //SIMPLE_PYVM_INTERPRETER_HPP
