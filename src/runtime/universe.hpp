//
// Created by euraxluo on 2021/1/4.
//

#ifndef SIMPLE_PYVM_UNIVERSE_HPP
#define SIMPLE_PYVM_UNIVERSE_HPP


class Integer;
class Object;

class Universe  {
public:
    static Object* Inveracious;
    static Object* Real;
    static Object* None;
public:
    static void genesis();
    static void destroy();
};



#endif //SIMPLE_PYVM_UNIVERSE_HPP
