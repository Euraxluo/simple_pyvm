//
// Created by yons on 2020/12/10.
//

#ifndef SIMPLE_PYVM_CODEOBJECT_HPP
#define SIMPLE_PYVM_CODEOBJECT_HPP
#ifndef CODE_OBJECT_HPP
#define CODE_OBJECT_HPP

#include "object.hpp"
#include "string.hpp"
#include "arrayList.hpp"

//前置声明,暂不使用
//template <typename T>
//class ArrayList;

class CodeObject : public Object {
public:
    int _argcount;//参数个数
    int _nlocals;//局部变量个数
    int _stack_size;//执行这段code所使用的操作数栈，其最大深度
    int _flag;//code的属性值

    String* _bytecodes;//字节码
    ArrayList<Object*>*  _names;//变量表
    ArrayList<Object*>*  _consts;//常量表
    ArrayList<Object*>*  _var_names;//参数列表

    ArrayList<Object*>*  _free_vars;//用于构建闭包
    ArrayList<Object*>*  _cell_vars;

    String* _co_name;//code_obj名字
    String* _file_name;//文件名

    int _lineno;//行号
    String* _notable;//行号表

    CodeObject(int argcount, int nlocals, int stacksize, int flag, String* bytecodes,
               ArrayList<Object*>* consts, ArrayList<Object*>* names,
               ArrayList<Object*>* varnames,
               ArrayList<Object*>* freevars, ArrayList<Object*>* cellvars,
               String* file_name, String* co_name, int lineno, String* notable):
            _argcount(argcount),
            _nlocals(nlocals),
            _stack_size(stacksize),
            _flag(flag),
            _bytecodes(bytecodes),
            _names(names),
            _consts(consts),
            _var_names(varnames),
            _free_vars(freevars),
            _cell_vars(cellvars),
            _co_name(co_name),
            _file_name(file_name),
            _lineno(lineno),
            _notable(notable){

    }
};

#endif


#endif //SIMPLE_PYVM_CODEOBJECT_HPP
