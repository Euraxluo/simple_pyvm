#include <iostream>
#include <stdio.h>
using namespace std;

#include "src/study/Study.hpp"

#define INIT 0
#define NUM 1


int main() {

    /***
     * Study space
     */
//    Study().var_type();
    Study().file_stu_1("test/hello.py");
    Study().const_char_stu();





    /***
     * Test space
     */


    /***
     * Main space
     */
//    FILE *fp = fopen("test/hello.py","r");
//    char ch;
//    int state,num = 0;
//    while ((ch=getc(fp)) != EOF){
//        if (ch == ' ' || ch == '\n'){
//            if (state == NUM){
//                cout<<"token NUM:%d\n"<<endl;
//            }
//        }
//    }
//
//
//    std::cout << "Hello, World!" << std::endl;
    return 0;
}


