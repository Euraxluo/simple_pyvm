//
// Created by euraxluo on 2020/11/22.
//

#ifndef PYTHONVM_STUDY_HPP
#define PYTHONVM_STUDY_HPP

#include<iostream>
#include <limits>

using namespace std;

class Study {
//https://www.runoob.com/cplusplus/cpp-files-streams.html
public:
    int var_type() {
        /**
        type:           ************size**************
        bool:           ��ռ�ֽ�����1   ���ֵ��1               ��Сֵ��0
        char:           ��ռ�ֽ�����1   ���ֵ��               ��Сֵ����
        signed char:    ��ռ�ֽ�����1   ���ֵ��               ��Сֵ����
        unsigned char:  ��ռ�ֽ�����1   ���ֵ��?              ��Сֵ��
        wchar_t:        ��ռ�ֽ�����2   ���ֵ��65535           ��Сֵ��0
        short:          ��ռ�ֽ�����2   ���ֵ��32767           ��Сֵ��-32768
        int:            ��ռ�ֽ�����4   ���ֵ��2147483647      ��Сֵ��-2147483648
        unsigned:       ��ռ�ֽ�����4   ���ֵ��4294967295      ��Сֵ��0
        long:           ��ռ�ֽ�����4   ���ֵ��2147483647      ��Сֵ��-2147483648
        unsigned long:  ��ռ�ֽ�����4   ���ֵ��4294967295      ��Сֵ��0
        double:         ��ռ�ֽ�����8   ���ֵ��1.79769e+308    ��Сֵ��2.22507e-308
        long double:    ��ռ�ֽ�����12  ���ֵ��1.18973e+4932   ��Сֵ��3.3621e-4932
        float:          ��ռ�ֽ�����4   ���ֵ��3.40282e+038    ��Сֵ��1.17549e-038
        size_t:

        size_t:         ��ռ�ֽ�����4   ���ֵ��4294967295      ��Сֵ��0
        string:         ��ռ�ֽ�����24
        type:           ************size**************
         */
        cout << "type: \t\t" << "************size**************" << endl;
        cout << "bool: \t\t" << "��ռ�ֽ�����" << sizeof(bool);
        cout << "\t���ֵ��" << (numeric_limits<bool>::max)();
        cout << "\t\t��Сֵ��" << (numeric_limits<bool>::min)() << endl;
        cout << "char: \t\t" << "��ռ�ֽ�����" << sizeof(char);
        cout << "\t���ֵ��" << (numeric_limits<char>::max)();
        cout << "\t\t��Сֵ��" << (numeric_limits<char>::min)() << endl;
        cout << "signed char: \t" << "��ռ�ֽ�����" << sizeof(signed char);
        cout << "\t���ֵ��" << (numeric_limits<signed char>::max)();
        cout << "\t\t��Сֵ��" << (numeric_limits<signed char>::min)() << endl;
        cout << "unsigned char: \t" << "��ռ�ֽ�����" << sizeof(unsigned char);
        cout << "\t���ֵ��" << (numeric_limits<unsigned char>::max)();
        cout << "\t\t��Сֵ��" << (numeric_limits<unsigned char>::min)() << endl;
        cout << "wchar_t: \t" << "��ռ�ֽ�����" << sizeof(wchar_t);
        cout << "\t���ֵ��" << (numeric_limits<wchar_t>::max)();
        cout << "\t\t��Сֵ��" << (numeric_limits<wchar_t>::min)() << endl;
        cout << "short: \t\t" << "��ռ�ֽ�����" << sizeof(short);
        cout << "\t���ֵ��" << (numeric_limits<short>::max)();
        cout << "\t\t��Сֵ��" << (numeric_limits<short>::min)() << endl;
        cout << "int: \t\t" << "��ռ�ֽ�����" << sizeof(int);
        cout << "\t���ֵ��" << (numeric_limits<int>::max)();
        cout << "\t��Сֵ��" << (numeric_limits<int>::min)() << endl;
        cout << "unsigned: \t" << "��ռ�ֽ�����" << sizeof(unsigned);
        cout << "\t���ֵ��" << (numeric_limits<unsigned>::max)();
        cout << "\t��Сֵ��" << (numeric_limits<unsigned>::min)() << endl;
        cout << "long: \t\t" << "��ռ�ֽ�����" << sizeof(long);
        cout << "\t���ֵ��" << (numeric_limits<long>::max)();
        cout << "\t��Сֵ��" << (numeric_limits<long>::min)() << endl;
        cout << "unsigned long: \t" << "��ռ�ֽ�����" << sizeof(unsigned long);
        cout << "\t���ֵ��" << (numeric_limits<unsigned long>::max)();
        cout << "\t��Сֵ��" << (numeric_limits<unsigned long>::min)() << endl;
        cout << "double: \t" << "��ռ�ֽ�����" << sizeof(double);
        cout << "\t���ֵ��" << (numeric_limits<double>::max)();
        cout << "\t��Сֵ��" << (numeric_limits<double>::min)() << endl;
        cout << "long double: \t" << "��ռ�ֽ�����" << sizeof(long double);
        cout << "\t���ֵ��" << (numeric_limits<long double>::max)();
        cout << "\t��Сֵ��" << (numeric_limits<long double>::min)() << endl;
        cout << "float: \t\t" << "��ռ�ֽ�����" << sizeof(float);
        cout << "\t���ֵ��" << (numeric_limits<float>::max)();
        cout << "\t��Сֵ��" << (numeric_limits<float>::min)() << endl;
        cout << "size_t: \t" << "��ռ�ֽ�����" << sizeof(size_t);
        cout << "\t���ֵ��" << (numeric_limits<size_t>::max)();
        cout << "\t��Сֵ��" << (numeric_limits<size_t>::min)() << endl;
        cout << "string: \t" << "��ռ�ֽ�����" << sizeof(string) << endl;
        // << "\t���ֵ��" << (numeric_limits<string>::max)() << "\t��Сֵ��" << (numeric_limits<string>::min)() << endl;
        cout << "type: \t\t" << "************size**************" << endl;
        return 0;
    }
    void const_char_stu() {
        char str[] = "hello world";
        char str2[] = "world";
        const char *pstr1 = str;
        char const *pstr2 = str;//ָ�룬ָ��char const
        char *const pstr3 = str;//const ָ�룬ָ��char

//        pstr1[0] = 's';//�����޷�ֱ�Ӹı�ָ��ָ���ֵ
//        pstr2[0] = 's';//�����޷�ֱ�Ӹı�ָ��ָ���ֵ
        pstr3[0] = 's';
        pstr1 = str2;
        pstr2 = str2;

        cout<<"pstr1:"<<pstr1<<endl;
        cout<<"pstr2:"<<pstr2<<endl;
        cout<<"pstr3:"<<pstr3<<endl;
//        pstr3 = str2;//�����޷��ı�ָ���ָ��

    }
    void file_stu_1(char const *filename) {
        FILE *fp;//�ļ�ָ��
        char str_buf[256];//�ַ�����char���飩
        fp = fopen(filename, "r");
        if (fp) {
            fgets(str_buf, 10, fp);
        } else {
            printf("cannot find file named %s\n", filename);
        }
    }
};


#endif //PYTHONVM_STUDY_HPP
