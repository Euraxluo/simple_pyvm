//
// Created by euraxluo on 2021/3/5.
//

#include "runtime/universe.hpp"
#include "klass.hpp"
#include "integer.hpp"
#include "string.hpp"
int Klass::compare_klass(Klass *x, Klass *y) {
    if (x == y)
        return 0;

    if (IntegerKlass::getInstance() == (IntegerKlass*)x)
        return -1;
    else if (IntegerKlass::getInstance() == (IntegerKlass*)y)
        return 1;

    if (x->name()->less(y->name()) == (Object *) Universe::Real)
        return -1;
    else
        return 1;
}