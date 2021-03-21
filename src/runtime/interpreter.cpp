//
// Created by euraxluo on 2021/1/4.
//
#include "interpreter.hpp"

Interpreter* Interpreter::_instance = nullptr;
Interpreter* Interpreter::getInstance(){
    if (_instance == nullptr) {
        _instance = new Interpreter();
    }

    return _instance;

}

Interpreter::Interpreter() {
    _builtins = new HashMap<Object *, Object *>();
    _builtins->put(new String("True"), BUILTIN_TRUE());
    _builtins->put(new String("False"), BUILTIN_FALSE());
    _builtins->put(new String("None"), BUILTIN_NONE());
    _builtins->put(new String("len"), new Function(len)); //native func
    _builtins->put(new String("abs"), new Function(abs)); //native func
    _builtins->put(new String("pow"), new Function(pow)); //native func
    _builtins->put(new String("complex"), new Function(complex)); //native func
    _builtins->put(new String("int"), new Function(int_func)); //native func
    _builtins->put(new String("float"), new Function(float_func)); //native func
    _builtins->put(new String("hex"), new Function(hex)); //native func
    _builtins->put(new String("oct"), new Function(oct)); //native func
    _builtins->put(new String("hash"), new Function(hash)); //native func

    _builtins->put(new String("type"),     new Function(type_of));
    _builtins->put(new String("isinstance"),new Function(isinstance));

    _builtins->put(new String("int"), (Object *) IntegerKlass::getInstance()->type());
    _builtins->put(new String("object"), (Object *) ObjectKlass::getInstance()->type());
    _builtins->put(new String("str"), (Object *) StringKlass::getInstance()->type());
    _builtins->put(new String("list"), (Object *) ListKlass::getInstance()->type());
    _builtins->put(new String("dict"), (Object *) MapKlass::getInstance()->type());
}
void Interpreter::run(CodeObject *co) {
    _frame = new FrameObject(co);
    _frame->locals()->put(new String("__name__"),new String("__main__"));
    eval_frame();
    destroy_frame();
}

Object* Interpreter::call_virtual (Object* func,ObjectArr args){
    if (func->klass() == NativeFunctionKlass::getInstance()) {
        // we do not create a virtual frame, but native frame.
        return ((Function*)func)->call(args);
    }
    else if (CheckKlass::isMethod(func)) {
        Method* method = (Method*) func;
        if (!args) {
            args = new ArrayList<Object*>(1);
        }
        args->insert(0, method->owner());
        return call_virtual(method->func(), args);
    }
    else if (CheckKlass::isFunction(func)) {
        int size = args ? args->size() : 0;
        //创建虚拟栈桢
        FrameObject* frame = new FrameObject((Function*) func, args, size);
        frame->set_entry_frame(true);

        //执行该栈
        enter_frame(frame);

        eval_frame();
        //销毁该桢，返回结果
        destroy_frame();
        return _ret_value;
    }

    return Universe::None;
}

void Interpreter::destroy_frame() {
    //切换栈桢，释放旧栈桢
    auto old_frame = _frame;
    _frame = _frame->sender();
    delete old_frame;

}

void Interpreter::leave_frame() {
    destroy_frame();
    PUSH(_ret_value);
}

void Interpreter::enter_frame(FrameObject* frame) {
    frame->set_sender(_frame);
    _frame         = frame;
}

void Interpreter::build_frame(Object *callable, ObjectArr args, int option_arg) {

    if (CheckKlass::isNative(callable)) {//NativeFunctionKlass
        PUSH(((Function *) callable)->call(args));


    } else if (CheckKlass::isMethod(callable)) {//MethodKlass
        Method *method = (Method *) callable;
        if (!args) {
            args = new ArrayList<Object *>(1);
        }
        args->insert(0, method->owner());
        build_frame(method->func(), args, option_arg + 1);


    } else if (CheckKlass::isFunction(callable)) {//FunctionKlass

        FrameObject *frame = new FrameObject((Function *) callable, args, option_arg);
        frame->set_sender(_frame);//一个指针，设置调用者的栈桢
        _frame = frame;


    } else if (CheckKlass::isType(callable)) {//FunctionKlass

        Object* instance = ((Type*)callable)->sign()->allocate_instance(callable,args);
        PUSH(instance);

    } else {
        Object* call = callable->getattr(StringTable::getInstance()->call_str);
        if (call != Universe::None){
            build_frame(call,args,option_arg);
        } else{
            callable->print();
            printf("\nError: can not call a normal object .\n");
        }
    }

}

void Interpreter::eval_frame() {
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
            case ByteCode::ROT_TWO:
                v = POP();
                w = POP();
                PUSH(v);
                PUSH(w);
                break;
            case ByteCode::ROT_THREE:
                v = POP(); //值
                w = POP(); //操作数
                u = POP(); //索引，操作数上的
                PUSH(v);
                PUSH(u);
                PUSH(w);
                break;
            case ByteCode::DUP_TOP:
                PUSH(TOP());
                break;
            case ByteCode::DUP_TOPX:
                for (int i = 0; i < option_arg; i++) {
                    int index = STACK_LEVEL() - option_arg;
                    PUSH(PEEK(index));
                }
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
            case ByteCode::BINARY_MULTIPLY:
                v = POP();
                w = POP();
                PUSH(w->mul(v));
                break;
            case ByteCode::BINARY_DIVIDE:
                v = POP();
                w = POP();
                PUSH(w->div(v));
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
                    case ByteCode::IN:
                        PUSH(w->contains(v));
                        break;
                    case ByteCode::NOT_IN:
                        PUSH(w->not_contains(v));
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
                if (option_arg > 0) {
                    int num_arg = option_arg & 0xff;//低8位代表位置参数的个数
                    int num_kwarg = option_arg >> 8;//高8位代表键参数个数

                    int arg_cnt = num_arg + 2 * num_kwarg;//真实的参数个数

                    //该字节码的参数是，函数参数个数
                    args = new ArrayList<Object *>(arg_cnt);
                    while (arg_cnt--) {
                        args->set(arg_cnt, POP());
                    }
                }
                build_frame(POP(), args, option_arg);//将栈顶的func对象取出，替换当前栈桢，运行frame内的字节码
                if (args != nullptr) {
                    delete args;
                    args = nullptr;
                }
                break;
            case ByteCode::MAKE_CLOSURE:
                v = POP();//此时栈上的对象是load_closure字节码加载的对象
                fo = new Function(v);
                fo->set_closure((List *) POP());//这个对象上次入栈时被转包装为了List；
                fo->set_globals(_frame->globals());
                if (option_arg > 0) {
                    args = new ArrayList<Object *>(option_arg);
                    while (option_arg--) {
                        args->set(option_arg, POP());
                    }
                }
                fo->set_default(args);

                if (args != nullptr) {
                    args = nullptr;
                }

                PUSH(fo);
                break;
            case ByteCode::RETURN_VALUE :
                _ret_value  = POP();
                if(_frame->is_frist_frame()||_frame->is_entry_frame())
                    return;
                leave_frame();
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
            case ByteCode::LOAD_CLOSURE:
                //从closure中取出对应序号的对象
                v = _frame->closure()->get(option_arg);
                //如果为空，说明这个值不是局部变量，而是一个参数
                if (v == nullptr) {
                    //将这个cell变量从参数列表中，再存到colure中
                    v = _frame->get_cell_from_parameter(option_arg);
                    _frame->closure()->set(option_arg, v);
                }
                if (v->klass() == CellKlass::getInstance()) {
                    PUSH(v);
                } else {
                    // _frame->closure()->set(option_arg,v);
                    //option_arg 是v在_frame->closure()中的序号
                    //_table是变量所在的表
                    PUSH(new CellObject(_frame->closure(), option_arg));
                }

                break;

            case ByteCode::LOAD_DEREF:
                //加载闭包变量
                v = _frame->closure()->get(option_arg);
                if (v->klass() == CellKlass::getInstance()) {
                    v = ((CellObject *) v)->value();
                }
                PUSH(v);
                break;
            case ByteCode::STORE_DEREF:
                _frame->closure()->set(option_arg, POP());
                break;
            case ByteCode::BUILD_LIST:
                v = new List();
                while (option_arg--) {
                    ((List *) v)->set(option_arg, POP());
                }
                PUSH(v);
                break;
            case ByteCode::BUILD_TUPLE:
                //todo 当前只是用list替代tuple
                v = new List(); //用来将闭包变量打包放到FO中
                while (option_arg--) {
                    ((List *) v)->set(option_arg, POP());
                }
                PUSH(v);
                break;

            case ByteCode::BINARY_SUBSCR:
                v = POP();
                w = POP();
                PUSH(w->subscr(v));
                break;
            case ByteCode::BINARY_SUBTRACT:
                v = POP();
                w = POP();
                PUSH(w->sub(v));
                break;
            case ByteCode::STORE_SUBSCR:
                u = POP();
                v = POP();
                w = POP();
                v->store_subscr(u, w);
                break;
            case ByteCode::DELETE_SUBSCR:
                w = POP();
                v = POP();
                v->del_subscr(w);
                break;
            case ByteCode::GET_ITER:
                v = POP();
                PUSH(v->iter());
                break;
            case ByteCode::FOR_ITER:
                v = TOP();
                //这里迭代时么有去查变量表。。所以只能拿对象的“next”属性
                w = v->getattr(StringTable::getInstance()->next_str);
                //不断地从build_frame中调用next方法
                build_frame(w, nullptr, option_arg);
                if (TOP() == nullptr) {
                    _frame->set_pc(_frame->get_pc() + option_arg);
                    POP();
                }
                break;
            case ByteCode::BUILD_MAP:
                v = new Map();
                while (option_arg--) {
                    PUSH(v);
                }
                PUSH(v);
                break;
            case ByteCode::STORE_MAP:
                w = POP();
                u = POP();
                v = POP();
                ((Map *) v)->put(w, u);
                break;
            case ByteCode::UNPACK_SEQUENCE:
                v = POP();
                while (option_arg--) {
                    PUSH(v->subscr(new Integer(option_arg)));
                }
                break;
            case ByteCode::CALL_FUNCTION_VAR:
                v = POP();
                if (option_arg > 0 || (v && ((List *) v)->size() > 0)) {
                    int na = option_arg & 0xff;
                    int nk = option_arg >> 8;
                    int arg_cnt = na + 2 * nk;
                    args = new ArrayList<Object *>();
                    while (arg_cnt--) {
                        args->set(arg_cnt, POP());
                    }

                    int s = ((List *) v)->size();
                    for (int i = 0; i < s; i++) {
                        args->push(((List *) v)->get(i));
                    }
                    na += s;
                    option_arg = (nk << 8) | na;
                }

                build_frame(POP(), args, option_arg);

                if (args != nullptr) {
                    args = nullptr;
                }
                break;
            case ByteCode::LOAD_LOCALS:
                PUSH(_frame->locals());
                break;
            case ByteCode::BUILD_CLASS:
                v = POP();
                u = POP();
                w = POP();
                v = Klass::create_klass(v,u,w);
                PUSH(v);
                break;
            case ByteCode::STORE_ATTR:
                u = POP();
                v = _frame->names()->get(option_arg);
                w = POP();
                u->setattr(v,w);
                break;
            default:
                printf("Error:Unrecongnized byte code %d\n", option_code);
        }
    }
}

