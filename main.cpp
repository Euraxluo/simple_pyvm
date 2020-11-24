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


int main(int argc,char** argv) {

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
     ArrayList<int > xx(1);
     xx.add(3);
     xx.add(4);
     printf("%d\n",xx.pop());


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


