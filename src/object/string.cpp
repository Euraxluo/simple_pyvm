//
// Created by euraxluo on 2021/1/21.
//

#include "string.hpp"
#include "klass.hpp"
#include "integer.hpp"
#include "runtime/universe.hpp"

StringKlass *StringKlass::_instance = nullptr;

StringKlass::StringKlass() {}

StringKlass::~StringKlass() {}

//初始化列表
String::String(size_t length) {
    _length = length;
    if (_length == 0) {
        _string = new char[1];
    } else {
        _string = new char[_length];
    }
    _string[_length] = '\0';
    setKlass(StringKlass::getInstance());
}

//char* 构造器
String::String(const char *str) {
    _length = 0;
    if (str) {
        _length = strlen(str);
        _string = new char[_length + 1];
        strcpy(_string, str);
    }
    _string[_length] = '\0';
    setKlass(StringKlass::getInstance());
}

//char* 构造器，但是可以指定长度,注意这里不要超出了字符的长度，否则会cpy到其他内存区
String::String(const char *x, size_t length) {
    _length = length;
    _string = new char[length];
    memcpy(_string, x, _length);
    setKlass(StringKlass::getInstance());
}

String::String(const size_t times, const char ch) {
    _length = times;
    _string = new char[_length + 1];
    *(_string + _length) = '\0';
    strset(_string, ch);
    setKlass(StringKlass::getInstance());
}

//拷贝构造

String::String(const String &str) {
    _length = str._length;
    _string = new char[_length + 1];
    strcpy(_string, str._string);
    setKlass(StringKlass::getInstance());
}

String::~String() {
    delete[] _string;
}

StringKlass *StringKlass::getInstance() {
    if (_instance == nullptr)
        _instance = new StringKlass();
    return _instance;
}

void StringKlass::print(Object *obj) {
    String *str = (String *) obj;
    assert(str && str->klass() == (Klass *) this);
    for (int i = 0; i < str->length(); i++) {
        printf("%c", str->c_str()[i]);
    }
}

//Object* StringKlass::less(Object *x, Object *y) {
//    String* sx = (String*) x;
//    assert(sx && (sx->klass() == (Klass *)this));
//
//    if (x->klass() != y->klass()) {
//        if (Klass::compare_klass(x->klass(), y->klass()) < 0)
//            return Universe::Real;
//        else
//            return Universe::Inveracious;
//    }
//
//    String* sy = (String*)y;
//    assert(sy && (sy->klass() == (Klass *)this));
//
//    int len = sx->length() < sy->length() ?
//              sx->length() : sy->length();
//
//    for (int i = 0; i < len; i++) {
//        if (sx->c_str()[i] < sy->c_str()[i])
//            return Universe::Real;
//        else if (sx->c_str()[i] > sy->c_str()[i])
//            return Universe::Inveracious;
//    }
//
//    if (sx->length() < sy->length()) {
//        return Universe::Real;
//    }
//
//    return Universe::Inveracious;
//}

Object *StringKlass::equal(Object *x, Object *y) {
    if (x->klass() != y->klass())
        return Universe::Inveracious;

    String *sx = (String *) x;
    String *sy = (String *) y;

    assert(sx && sx->klass() == (Klass *) this);
    assert(sy && sy->klass() == (Klass *) this);

    if (sx->length() != sy->length())
        return Universe::Inveracious;

    for (int i = 0; i < sx->length(); i++) {
        if (sx->c_str()[i] != sy->c_str()[i])
            return Universe::Inveracious;
    }

    return Universe::Real;
}

Object *StringKlass::not_equal(Object *x, Object *y) {
    if (x->klass() != y->klass())
        return Universe::Real;

    String *sx = (String *) x;
    String *sy = (String *) y;

    assert(sx && sx->klass() == (Klass *) this);
    assert(sy && sy->klass() == (Klass *) this);

    if (sx->length() != sy->length())
        return Universe::Real;

    for (int i = 0; i < sx->length(); i++) {
        if (sx->c_str()[i] != sy->c_str()[i])
            return Universe::Real;
    }

    return Universe::Inveracious;
}

Object *StringKlass::add(Object *x, Object *y) {
    assert(x && x->klass() == this);
    assert(y && y->klass() == this);

    String *sx = (String *) x;
    String *sy = (String *) y;
    String* sz = new String();
    sz->append(sx->c_str());
    sz->append(sy->c_str());
    sz->insert(sx->length() + sy->length(), '\0');
    return sz;
}


Object *StringKlass::i_add(Object *x, Object *y) {
    assert(x && x->klass() == this);
    assert(y && y->klass() == this);

    String *sx = (String *) x;
    String *sy = (String *) y;

    String *sz = new String(sx->length() + sy->length());
    sz->memcpy(sz->_str(), sx->c_str(), sx->length());
    sz->memcpy(sz->_str() + sx->length(),
               sy->c_str(),
               sy->length());

    sz->insert(sx->length() + sy->length(), '\0');

    return sz;
}
