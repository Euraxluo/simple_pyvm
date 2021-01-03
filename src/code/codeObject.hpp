//
// Created by yons on 2020/12/10.
//

#ifndef CODE_OBJECT_HPP
#define CODE_OBJECT_HPP

//前置声明,暂不使用
//template <typename T>
//class ArrayList;
#include "helper.hpp"

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

    inline const char* toString(){
        if (this == nullptr){
            return "null";
        }
        String to_string;
        char* intv = new char[16];
        String * bytecodesHex = Helper::string2hex(_bytecodes);
        String * notableHex = Helper::string2hex(_notable);
        to_string="_argcount(";
        to_string+=String::int2String(_argcount,intv);
        to_string+="),";
        to_string+="_nlocals(";
        to_string+=String::int2String(_nlocals,intv);
        to_string+="),";
        to_string+="_stack_size(";
        to_string+=String::int2String(_stack_size,intv);
        to_string+="),";
        to_string+="_flag(";
        to_string+=String::int2String(_flag,intv);
        to_string+="),";
        to_string=to_string+"_bytecodes("+bytecodesHex->c_str()+"),";
        to_string+="_names[";
        for (int i = 0; i < _names->size(); ++i) {
            auto o=  _names->get(i);
            to_string+=o->toString();
        }
        to_string+="],";
        to_string+="_consts[";
        for (int i = 0; i < _consts->size(); ++i) {
            auto o=  _consts->get(i);
            to_string+=o->toString();
        }
        to_string+="],";
        to_string+="_var_names[";
        for (int i = 0; i < _var_names->size(); ++i) {
            auto o=  _var_names->get(i);
            to_string+=o->toString();
        }
        to_string+="],";
        to_string+="_free_vars[";
        for (int i = 0; i < _free_vars->size(); ++i) {
            auto o=  _free_vars->get(i);
            to_string+=o->toString();
        }
        to_string+="],";
        to_string+="_cell_vars[";
        for (int i = 0; i < _cell_vars->size(); ++i) {
            auto o=  _cell_vars->get(i);
            to_string+=o->toString();
        }
        to_string+="],";
        to_string=to_string+"_co_name("+*_co_name+"),";
        to_string=to_string+"_file_name("+*_file_name+"),";
        to_string+="_lineno(";
        to_string+=String::int2String(_lineno,intv);
        to_string+="),";
        to_string=to_string+"_notable("+notableHex->c_str()+")";

        //避免幽灵变量
        String * string = new String(to_string);
        delete bytecodesHex;
        delete intv;
        return string->toString();
    }
};

#endif