
//
// Created by euraxluo on 2020/11/22.
//

#ifndef PYTHONVM_STUDY_HPP
#define PYTHONVM_STUDY_HPP

#include<iostream>
#include <limits>

using namespace std;

class study {
public:
    int var_type() {
        /**
        type:           ************size**************
        bool:           所占字节数：1   最大值：1               最小值：0
        char:           所占字节数：1   最大值：               最小值：€
        signed char:    所占字节数：1   最大值：               最小值：€
        unsigned char:  所占字节数：1   最大值：?              最小值：
        wchar_t:        所占字节数：2   最大值：65535           最小值：0
        short:          所占字节数：2   最大值：32767           最小值：-32768
        int:            所占字节数：4   最大值：2147483647      最小值：-2147483648
        unsigned:       所占字节数：4   最大值：4294967295      最小值：0
        long:           所占字节数：4   最大值：2147483647      最小值：-2147483648
        unsigned long:  所占字节数：4   最大值：4294967295      最小值：0
        double:         所占字节数：8   最大值：1.79769e+308    最小值：2.22507e-308
        long double:    所占字节数：12  最大值：1.18973e+4932   最小值：3.3621e-4932
        float:          所占字节数：4   最大值：3.40282e+038    最小值：1.17549e-038
        size_t:
        size_t:         所占字节数：4   最大值：4294967295      最小值：0
        string:         所占字节数：24
        type:           ************size**************
         */
        cout << "type: \t\t" << "************size**************" << endl;
        cout << "bool: \t\t" << "所占字节数：" << sizeof(bool);
        cout << "\t最大值：" << (numeric_limits<bool>::max)();
        cout << "\t\t最小值：" << (numeric_limits<bool>::min)() << endl;
        cout << "char: \t\t" << "所占字节数：" << sizeof(char);
        cout << "\t最大值：" << (numeric_limits<char>::max)();
        cout << "\t\t最小值：" << (numeric_limits<char>::min)() << endl;
        cout << "signed char: \t" << "所占字节数：" << sizeof(signed char);
        cout << "\t最大值：" << (numeric_limits<signed char>::max)();
        cout << "\t\t最小值：" << (numeric_limits<signed char>::min)() << endl;
        cout << "unsigned char: \t" << "所占字节数：" << sizeof(unsigned char);
        cout << "\t最大值：" << (numeric_limits<unsigned char>::max)();
        cout << "\t\t最小值：" << (numeric_limits<unsigned char>::min)() << endl;
        cout << "wchar_t: \t" << "所占字节数：" << sizeof(wchar_t);
        cout << "\t最大值：" << (numeric_limits<wchar_t>::max)();
        cout << "\t\t最小值：" << (numeric_limits<wchar_t>::min)() << endl;
        cout << "short: \t\t" << "所占字节数：" << sizeof(short);
        cout << "\t最大值：" << (numeric_limits<short>::max)();
        cout << "\t\t最小值：" << (numeric_limits<short>::min)() << endl;
        cout << "int: \t\t" << "所占字节数：" << sizeof(int);
        cout << "\t最大值：" << (numeric_limits<int>::max)();
        cout << "\t最小值：" << (numeric_limits<int>::min)() << endl;
        cout << "unsigned: \t" << "所占字节数：" << sizeof(unsigned);
        cout << "\t最大值：" << (numeric_limits<unsigned>::max)();
        cout << "\t最小值：" << (numeric_limits<unsigned>::min)() << endl;
        cout << "long: \t\t" << "所占字节数：" << sizeof(long);
        cout << "\t最大值：" << (numeric_limits<long>::max)();
        cout << "\t最小值：" << (numeric_limits<long>::min)() << endl;
        cout << "unsigned long: \t" << "所占字节数：" << sizeof(unsigned long);
        cout << "\t最大值：" << (numeric_limits<unsigned long>::max)();
        cout << "\t最小值：" << (numeric_limits<unsigned long>::min)() << endl;
        cout << "double: \t" << "所占字节数：" << sizeof(double);
        cout << "\t最大值：" << (numeric_limits<double>::max)();
        cout << "\t最小值：" << (numeric_limits<double>::min)() << endl;
        cout << "long double: \t" << "所占字节数：" << sizeof(long double);
        cout << "\t最大值：" << (numeric_limits<long double>::max)();
        cout << "\t最小值：" << (numeric_limits<long double>::min)() << endl;
        cout << "float: \t\t" << "所占字节数：" << sizeof(float);
        cout << "\t最大值：" << (numeric_limits<float>::max)();
        cout << "\t最小值：" << (numeric_limits<float>::min)() << endl;
        cout << "size_t: \t" << "所占字节数：" << sizeof(size_t);
        cout << "\t最大值：" << (numeric_limits<size_t>::max)();
        cout << "\t最小值：" << (numeric_limits<size_t>::min)() << endl;
        cout << "string: \t" << "所占字节数：" << sizeof(string) << endl;
        // << "\t最大值：" << (numeric_limits<string>::max)() << "\t最小值：" << (numeric_limits<string>::min)() << endl;
        cout << "type: \t\t" << "************size**************" << endl;
        return 0;
    }

    void const_char_stu() {
        char str[] = "hello world";
        char str2[] = "world";
        const char *pstr1 = str;
        char const *pstr2 = str;//指针，指向char const
        char *const pstr3 = str;//const 指针，指向char

//        pstr1[0] = 's';//报错，无法直接改变指针指向的值
//        pstr2[0] = 's';//报错，无法直接改变指针指向的值
        pstr3[0] = 's';
        pstr1 = str2;
        pstr2 = str2;

        cout<<"pstr1:"<<pstr1<<endl;
        cout<<"pstr2:"<<pstr2<<endl;
        cout<<"pstr3:"<<pstr3<<endl;
//        pstr3 = str2;//报错，无法改变指针的指向

    }

    void file_stu_1(char const *filename) {
        FILE *fp;//文件指针
        char str_buf[256];//字符串（char数组）
        fp = fopen(filename, "r");
        if (fp) {
            fgets(str_buf, 10, fp);
        } else {
            printf("cannot find file named %s\n", filename);
        }
    }
    void test_0_x_ff(){
        signed int t = 257;
        t = t & 0xff;
        printf("%d",t);
//        signed
    }
    auto adder(){
        auto sum = 0;
        return [=] (int value) mutable{
            sum+=value;
            return sum;
        };
    }
};


#endif //PYTHONVM_STUDY_HPP