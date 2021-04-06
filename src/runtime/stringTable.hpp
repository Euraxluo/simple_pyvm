//
// Created by euraxluo on 2021/3/6.
//

#ifndef SIMPLE_PYVM_STRINGTABLE_HPP
#define SIMPLE_PYVM_STRINGTABLE_HPP

class String;
class StringTable {
private:
    static StringTable* _instance;
    StringTable();

public:
    static StringTable* getInstance();
    String* pyc_suf;
    String* name_str;
    String* builtins_str;
    String* main_str;
    String* next_str;
    String* mod_str;
    String* init_str;
    String* call_str;
    String* getitem_str;
    String* setitem_str;
    String* setattr_str;
    String* getattr_str;

    String* len_str;
    String* abs_str;
    String* pow_str;
    String* complex_str;
    String* int_str;
    String* float_str;
    String* hex_str;
    String* oct_str;
    String* hash_str;

    String* add_str;
    String* sub_str;
    String* mul_str;
    String* div_str;
    String* neg_str;
    String* lt_str;
    String* gt_str;
    String* le_str;
    String* ge_str;
    String* eq_str;
    String* ne_str;
    String* and_str;
    String* or_str;
    String* invert_str;
    String* xor_str;
};


#endif //SIMPLE_PYVM_STRINGTABLE_HPP
