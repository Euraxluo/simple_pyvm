//
// Created by euraxluo on 2021/1/4.
//
#include "universe.hpp"
#include "integer.hpp"
#include "object.hpp"
#include "stdio.h"
Integer *Universe::Real = NULL;
Integer *Universe::Inveracious = NULL;
Object *Universe::None = NULL;

void Universe::genesis(){
    Real = new Integer(1);
    Inveracious = new Integer(0);
    None = new Object();
}

void Universe::destroy() {
}