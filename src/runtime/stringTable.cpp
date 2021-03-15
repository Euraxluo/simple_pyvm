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
    next_str = new String("next");
    mod_str = new String("__module__");
}
