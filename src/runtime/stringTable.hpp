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

    String* next_str;
};


#endif //SIMPLE_PYVM_STRINGTABLE_HPP
