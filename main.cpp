#include <iostream>
#include <stdio.h>

using namespace std;

#include "src/study/study.hpp"
#include "src/util/bufferedInputStream.hpp"
#include "src/object/object.hpp"
#include "src/object/string.hpp"
#include "src/util/arrayList.hpp"

#define INIT 0
#define NUM 1
size_t StringSize(const char *s) {
    const char *p = s;
    while (*p != '\0'){
        printf("%c",*p);
        p++;
    }

    while(*p == '\0'){
        p++;
        printf("\\0");
    }
    printf(" ");
    return p - s;
}
void Test(){
    arrayList<int> xx(5);
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

    String str("123");

    str = "abc";

    printf("%s\n",str.c_str());
    printf("%d\n",str.length());
    printf("%s\n",*(str.c_addr()));
    printf("%d\n",StringSize(str.c_str()));

    const char* orginStr = "hello world";
    printf("%s\n",orginStr);
    String str1(orginStr);

    printf("%s\n",str1.c_str());
    printf("%d\n",str1.length());
    printf("%s\n",*(str1.c_addr()));
    printf("%d\n",StringSize(str1.c_str()));

    String str2 = str1;
    printf("%s\n",str2.c_str());
    printf("%d\n",str2.length());
    printf("%s\n",*(str2.c_addr()));
    printf("%d\n",StringSize(str2.c_str()));

    String str3(str1);
    printf("%s\n",str3.c_str());
    printf("%d\n",str3.length());
    printf("%s\n",*(str3.c_addr()));
    printf("%d\n",StringSize(str3.c_str()));

    String str4;
    str4+="13123";
    str4+=str1;
    str4=str4+"abc";
    str4=str4+"23123";
    str4.append("xixixi");
    str4.append(str2);
    printf("%s\n",str4.c_str());
    printf("%d\n",str4.length());
    printf("%s\n",*(str4.c_addr()));
    printf("%d\n",StringSize(str4.c_str()));
    char *x = &str4[6];//[]重载测试
    printf("%s\n",x);
    printf("%c\n",str4[3]);//[]重载测试

    char z = str4[11];
    printf("%c\n",z);

    if (str3==str4){
        printf("yes\n");
    }

    if (str3.empty()){
        printf("empty\n");
    }

    String str5;
    if (str5.empty()){
        printf("empty\n");
    }

}
void Stu(){
    study().var_type();
    study().test_0_x_ff();
    study().file_stu_1("test/hello.py");
    study().const_char_stu();
}

int main(int argc, char **argv) {

    /***
     * study space
     */
    Stu();
    /***
     * Test space
     */
    Test();

    /***
     * Main space
     */
    std::cout << "Hello, VM!" << std::endl;

    if (argc <= 1) {
        printf("vm need a parameter : filename\n");
        return 0;
    }

    bufferedInputStream stream(argv[1]);
    printf("\nmagic number is 0x%x\n", stream.read_int());

    return 0;
}


