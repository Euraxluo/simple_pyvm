#include <iostream>
#include <stdio.h>

using namespace std;

#include "src/study/Study.hpp"
#include "src/util/BufferedInputStream.hpp"
#include "src/object/HiObject.hpp"
#include "src/object/HiString.hpp"
#include "src/util/ArrayList.hpp"

#define INIT 0
#define NUM 1


int main(int argc, char **argv) {

    /***
     * Study space
     */
//    Study().var_type();
//    Study().test_0_x_ff();
//    Study().file_stu_1("test/hello.py");
//    Study().const_char_stu();





    /***
     * Test space
     */
    ArrayList<int> xx(5);
    xx.push(1);
    xx.push(2);
    xx.push(3);
    xx.push(4);
    xx.push(5);
    xx.push(6);
    xx.push(7);
    xx.push(8);
    xx.push(9);
    xx.pop();
    xx.pop();
    xx.pop();
    xx.pop();
    xx.pop();
    xx.pop();
    xx.pop();

    printf("%d\n", xx.size());
    printf("%d\n", xx.capacity());
    printf("%d\n\n\n", xx.length());

    xx.insert(0, 0);
    printf("size:%d\n", xx.size());
    xx.remove(4);
    printf("size:%d\n", xx.size());
    xx.set(4, 4);
    xx.set(6, 4);


    printf("size:%d\n", xx.size());

    printf("%d\n", xx.get(0));
    printf("%d\n", xx.get(1));
    printf("%d\n", xx.get(2));
    printf("%d\n", xx.get(3));
    printf("%d\n", xx.get(4));
    printf("%d\n", xx.get(5));
    printf("%d\n", xx.get(6));
    printf("%d\n", xx.size());
    printf("%d\n", xx.capacity());
    printf("%d\n", xx.length());


    /***
     * Main space
     */
    std::cout << "Hello, VM!" << std::endl;

    if (argc <= 1) {
        printf("vm need a parameter : filename\n");
        return 0;
    }

    BufferedInputStream stream(argv[1]);
    printf("\nmagic number is 0x%x\n", stream.read_int());

    return 0;
}


