#include <iostream>
#include <stdio.h>
#include <runtime/interpreter.hpp>

using namespace std;

#include "src/study/study.hpp"
#include "src/object/object.hpp"
#include "src/object/string.hpp"
#include "src/util/arrayList.hpp"
#include "src/util/bufferedInputStream.hpp"
#include "src/code/binaryFileParser.hpp"
#include "hashMap.hpp"

#define INIT 0
#define NUM 1

size_t StringSize(const char *s) {
    const char *p = s;
    while (*p != '\0') {
        printf("%c", *p);
        p++;
    }

    while (*p == '\0') {
        p++;
        printf("\\0");
    }
    printf(" ");
    return p - s;
}


void Stu() {
    Study().var_type();
    Study().test_0_x_ff();
    Study().file_stu_1("test/hello.py");
    Study().const_char_stu();

    auto adder = Study().adder();
    for (int i = 0; i < 10; ++i) {
        printf("%d\n", adder(i));
    }
}


void Test() {
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

    printf("%u\n", xx.size());
    printf("%u\n", xx.capacity());
    printf("%u\n\n\n", xx.length());

    xx.insert(0, 0);
    printf("size:%u\n", xx.size());
    xx.remove(4);
    printf("size:%u\n", xx.size());
    xx.set(4, 4);
    xx.set(6, 4);


    printf("size:%u\n", xx.size());

    printf("%d\n", xx.get(0));
    printf("%d\n", xx.get(1));
    printf("%d\n", xx.get(2));
    printf("%d\n", xx.get(3));
    printf("%d\n", xx.get(4));
    printf("%d\n", xx.get(5));
    printf("%d\n", xx.get(6));
    printf("%u\n", xx.size());
    printf("%u\n", xx.capacity());
    printf("%u\n", xx.length());

    String str("123");

    str = "abc";

    printf("%s\n", str.c_str());
    printf("%lu\n", str.length());
    printf("%s\n", *(str.c_addr()));
    printf("%lu\n", StringSize(str.c_str()));

    const char *orginStr = "hello world";
    printf("%s\n", orginStr);
    String str1(orginStr);

    printf("%s\n", str1.c_str());
    printf("%lu\n", str1.length());
    printf("%s\n", *(str1.c_addr()));
    printf("%lu\n", StringSize(str1.c_str()));

    String str2 = str1;
    printf("%s\n", str2.c_str());
    printf("%lu\n", str2.length());
    printf("%s\n", *(str2.c_addr()));
    printf("%lu\n", StringSize(str2.c_str()));

    String str3(str1);
    printf("%s\n", str3.c_str());
    printf("%lu\n", str3.length());
    printf("%s\n", *(str3.c_addr()));
    printf("%lu\n", StringSize(str3.c_str()));

    String str4;
    str4 += "13123";
    str4 += str1;
    str4 = str4 + "abc";
    str4 = str4 + "23123";
    str4.append("xixixi");
    str4.append(str2);
    printf("%s\n", str4.c_str());
    printf("%lu\n", str4.length());
    printf("%s\n", *(str4.c_addr()));
    printf("%lu\n", StringSize(str4.c_str()));
    char *x = &str4[6];//[]重载测试
    printf("%s\n", x);
    printf("%c\n", str4[3]);//[]重载测试

    char z = str4[11];
    printf("%c\n", z);

    if (str3 == str4) {
        printf("yes\n");
    }

    if (str3.empty()) {
        printf("empty\n");
    }

    String str5;
    if (str5.empty()) {
        printf("empty\n");
    }

}

unsigned int testMyHash(int i) {
    return i * 2;
}

void MapTest() {



//    HashMap<int,int>* hashMap = new HashMap<int,int>(9,&testMyHash);
//    size_t x = hashMap->hash(9);
//    size_t y = hashMap->hash(10);
//    size_t z = hashMap->hash(9);
//    size_t a = hashMap->hash(9);
//    size_t b = hashMap->hash(9);
//    printf("%lu %lu %lu %lu %lu\n",x,y,z,a,b);

//    HashMap<int,int>* hashMap = new HashMap<int,int>(9,&intHash);
//    size_t x = hashMap->hash(9);
//    size_t y = hashMap->hash(10);
//    size_t z = hashMap->hash(9);
//    size_t a = hashMap->hash(9);
//    size_t b = hashMap->hash(9);
//    printf("%lu %lu %lu %lu %lu\n",x,y,z,a,b);

//    HashMap<char *,int>* hashMap = new HashMap<char*,int>(9,&DJBHash);
//    String str("abc");
//    String str1("acb");
//    String str2(" abc");
//    String str3("abcd");
//    String str4("a_bc");
//    String str5("a_bc");
//    size_t x = hashMap->hash((char *)str.c_str());
//    size_t y = hashMap->hash((char *)str1.c_str());
//    size_t z = hashMap->hash((char *)str2.c_str());
//    size_t a = hashMap->hash((char *)str3.c_str());
//    size_t b = hashMap->hash((char *)str4.c_str());
//    size_t c = hashMap->hash((char *)str5.c_str());
//    printf("%lu %lu %lu %lu %lu %lu\n",x,y,z,a,b,c);

    HashMap<String *, int> *hashMap = new HashMap<String *, int>(&hashCode);
    String str("abc");
    String str1("ac1b");
    String str2(" a_bcd");
    String str3("abcd");
    String str4("a_bc");
    String str5("a_bcd");
    String str6("a_bc1");
    String str7("a_bc2");
    String str8("a_bc3");
//    printf("get1 %d\n",hashMap->get(&str, 0));
//    hashMap->put(&str, 31);
//    printf("get2 %d\n",hashMap->get(&str, 0));
//    hashMap->put(&str1, 1);
//    printf("get3 %d\n",hashMap->get(&str, 0));
//    hashMap->put(&str2, 2);
//    printf("get4 %d\n",hashMap->get(&str, 0));
//    hashMap->put(&str3, 3);
//    printf("get5 %d\n",hashMap->get(&str, 0));
//    hashMap->put(&str4, 4);
//    printf("get6 %d\n",hashMap->get(&str, 0));
//    hashMap->put(&str5, 5);
//    printf("get7 %d\n",hashMap->get(&str, 0));
//    hashMap->put(&str6, 6);
//    printf("get8 %d\n",hashMap->get(&str, 0));
//    hashMap->put(&str7, 7);
//    printf("get9 %d\n",hashMap->get(&str, 0));
//    hashMap->put(&str8, 8);
//    printf("get10 %d\n",hashMap->get(&str, 0));

    printf("%d %d %d %d %d %d %d %d %d\n",
           hashMap->hash_key(&str),
           hashMap->hash_key(&str1),
           hashMap->hash_key(&str2),
           hashMap->hash_key(&str3),
           hashMap->hash_key(&str4),
           hashMap->hash_key(&str5),
           hashMap->hash_key(&str6),
           hashMap->hash_key(&str7),
           hashMap->hash_key(&str8));

    hashMap->remove(&str);
    hashMap->remove(&str1);
    hashMap->remove(&str2);
    hashMap->remove(&str3);
    hashMap->remove(&str4);
    hashMap->remove(&str5);
    hashMap->remove(&str6);
    hashMap->remove(&str7);
    hashMap->remove(&str8);
//    hashMap->put(&str, 1);
//    hashMap->put(&str1, 2);

    printf("%d %d %d %d %d %d %d %d %d\n",
           hashMap->get(&str, 0),
           hashMap->get(&str1, 0),
           hashMap->get(&str2, 0),
           hashMap->get(&str3, 0),
           hashMap->get(&str4, 0),
           hashMap->get(&str5, 0),
           hashMap->get(&str6, 0),
           hashMap->get(&str7, 0),
           hashMap->get(&str8, 0));

    delete hashMap;

//    HashMap<String,int>* hashMap = new HashMap<String,int>(9,&hashCode);
//    String str("abc");
//    String str1("acb");
//    String str2(" abc");
//    String str3("abcd");
//    String str4("a_bc");
//    String str5("a_bc");
//    size_t x = hashMap->hash(str);
//    size_t y = hashMap->hash(str1);
//    size_t z = hashMap->hash(str2);
//    size_t a = hashMap->hash(str4);
//    size_t b = hashMap->hash(str5);
//    printf("%lu %lu %lu %lu %lu\n",x,y,z,a,b);


//    HashTable<int,int> mm;



//    String str3(str1);
}

int main(int argc, char **argv) {


    /***
     * study space
     */
//    Stu();
    /***
     * Test space
     */
//    Test();
//    MapTest();//TODO have bug
    /***
     * Main space
     */
    std::cout << "Hello, VM!" << std::endl;

    if (argc <= 1) {
        printf("vm need a parameter : filename\n");
        return 0;
    }


    BufferedInputStream stream(argv[1]);
    BinaryFileParser parser(&stream);
    CodeObject *main_code = parser.parse();
    printf("main_code is %s \n", main_code->toString());

    Universe::genesis();//初始化一些值
    Interpreter interpreter;



    interpreter.run(main_code);
    return 0;
}


