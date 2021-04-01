//
// Created by euraxluo on 2021/3/6.
//

#include "string.hpp"
#include "stringTable.hpp"
StringTable* StringTable::_instance = nullptr;

StringTable* StringTable::getInstance(){
    if (_instance == nullptr)
        _instance = new StringTable();

    return _instance;
}

StringTable::StringTable() {
    name_str = new String("__name__");
    builtins_str = new String("__builtins__");
    main_str = new String("__main__");
    next_str = new String("next");
    mod_str = new String("__module__");
    init_str = new String("__init__");
    call_str = new String("__call__");
    setitem_str = new String("__setitem__");
    getitem_str = new String("__getitem__");
    setattr_str = new String("__setattr__");
    getattr_str = new String("__getattr__");

    len_str = new String("__len__");
    abs_str = new String("__abs__");
    pow_str = new String("__pow__");
    int_str = new String("__int__");
    float_str = new String("__float__");
    complex_str = new String("__complex__");
    hex_str = new String("__hex__");
    oct_str = new String("__oct__");
    hash_str = new String("__hash__");


    add_str = new String("__add__");
    sub_str = new String("__sub__");
    mul_str = new String("__mul__");
    div_str = new String("__div__");
    neg_str = new String("__neg__");
    lt_str = new String("__lt__");
    gt_str = new String("__gt__");
    le_str = new String("__le__");
    ge_str = new String("__ge__");
    eq_str = new String("__eq__");
    ne_str = new String("__ne__");
    and_str = new String("__and__");
    or_str = new String("__or__");
    invert_str = new String("__invert__");
    xor_str = new String("__xor__");
}
