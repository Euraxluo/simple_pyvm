//
// Created by euraxluo on 2021/4/1.
//

#include "module.hpp"
#include "map.hpp"
#include "type.hpp"
#include "util/bufferedInputStream.hpp"
#include "code/binaryFileParser.hpp"
#include "runtime/interpreter.hpp"
ModuleKlass* ModuleKlass::_instance = NULL;

ModuleKlass* ModuleKlass::getInstance() {
    if (_instance == NULL)
        _instance = new ModuleKlass();

    return _instance;
}

void ModuleKlass::initialize() {

    set_klass_dict(new Map());
    (new Type())->setSign(this);
    setName(new String("module"));
    setSuper(ObjectKlass::getInstance());
}

Module::Module(Map* map) {
    set_obj_dict(map);
    setKlass(ModuleKlass::getInstance());
}

Module* Module::import_module(Object* x) {
    String* mod_name = (String*)x;
    String* file_name = (String*)(mod_name->add(new String(".pyc")));
    BufferedInputStream::getInstance()->readFileName(file_name->c_str());
    BinaryFileParser parser(BufferedInputStream::getInstance());
    CodeObject* mod_code = parser.parse();
    Map* mod_dict = Interpreter::getInstance()->run_mod(mod_code, mod_name);
    return new Module(mod_dict);
}

void Module::put(Object* x, Object* y) {
    obj_dict()->put(x, y);
}

Object* Module::get(Object* x) {
    return obj_dict()->get(x);
}
