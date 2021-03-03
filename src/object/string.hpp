//
// Created by euraxluo on 2021/1/21.
//

#ifndef SIMPLE_PYVM_STRING_HPP
#define SIMPLE_PYVM_STRING_HPP

#include "klass.hpp"
#include "object.hpp"
#include "stdio.h"

class StringKlass : public Klass {
private:
    static StringKlass *_instance;

    StringKlass();

    ~StringKlass();

public:
    static StringKlass *getInstance();

    virtual void print(Object *obj);

    //Klass Function

//    virtual Object *greater(Object *x, Object *y);

//    virtual Object *less(Object *x, Object *y);

    virtual Object *equal(Object *x, Object *y);

    virtual Object *not_equal(Object *x, Object *y);

//    virtual Object *ge(Object *x, Object *y);

//    virtual Object *le(Object *x, Object *y);

    virtual Object *add(Object *x, Object *y);

    virtual Object *i_add(Object *x, Object *y);

//    virtual Object *sub(Object *x, Object *y);
//
//    virtual Object *mul(Object *x, Object *y);
//
//    virtual Object *div(Object *x, Object *y);
//
//    virtual Object *mod(Object *x, Object *y);

    //Native Function
    virtual Object *len(Object *x);

    //Klass Function
    virtual Object *upper(Object *args);

    //type function
    virtual Object *subscr(Object *x, Object *y);

};

class String : public Object {
protected:
    char *_string = nullptr;
    size_t _length = 0;

    inline char *strcpy(char *dst, const char *src) {
        char *ret = dst;
        memcpy(dst, src, strlen(src) + 1);
        return ret;
    }


    inline size_t strlen(const char *s) {
        const char *p = s;
        while (*p != '\0')
            p++;
        return p - s;
    }

    inline char *strset(char *str, int val) {
        char *p = str;
        while (*str) {
            *str++ = (char) val;
        }
        return p;
    }

    inline char *strcat(char *s, const char *append) {
        char *save = s;
        for (; *s; ++s);
        while ((*s++ = *append++) != '\0');
        return (save);
    }

    inline char *strinsert(char *s, int index, const char append) {
        s[index] = append;
        return s;
    }

    inline int strcmp(const char *str1, const char *str2) {
        if (!str1 or !str2)
            return 1;
        while (*str1 && *str2 && (*str1 == *str2)) {
            ++str1;
            ++str2;
        }
        return *str1 - *str2;
    }

public:
    //初始化列表
    String(size_t length = 0);

    //char* 构造器
    String(const char *str);

    //char* 构造器，但是可以指定长度,注意这里不要超出了字符的长度，否则会cpy到其他内存区
    String(const char *x, size_t length);

    String(const size_t times, const char ch);

    //拷贝构造
    String(const String &str);

    ~String();

    inline const char *c_str() {
        return _string;
    }

    inline char *_str() {
        return _string;
    }

    inline size_t length() {
        return _length;
    }

    inline void *memcpy(void *dst, const void *src, size_t count) {
        void *ret = dst;
        if (dst <= src || (char *) dst >= ((char *) src + count))//源地址和目的地址不重叠，低字节向高字节拷贝
        {
            while (count--) {
                *(char *) dst = *(char *) src;
                dst = (char *) dst + 1;
                src = (char *) src + 1;
            }
        } else//源地址和目的地址重叠，高字节向低字节拷贝
        {
            dst = (char *) dst + count - 1;
            src = (char *) src + count - 1;
            while (count--) {
                *(char *) dst = *(char *) src;
                dst = (char *) dst - 1;
                src = (char *) src - 1;
            }
        }
        return ret;
    }

    inline bool empty() {
        return _length == 0 ? true : false;
    }

    inline char **c_addr() {
        return &_string;
    }

    inline String &append(const String &str) {
        *this += str;//重载
        return *this;
    }

    inline String &append(const char *str) {
        _length += strlen(str);
        char *old_str = _string;
        _string = new char[_length + 1];
        strcpy(_string, old_str);
        delete[] old_str;
        strcat(_string, str);
        return *this;
    }

    inline String &insert(size_t index, const char str) {
        assert(index >= 0 && index <= _length);
        strinsert(_string, index, str);
        return *this;
    }

    /**以下是重载运算符*/
    inline char &operator[](const size_t index) {
        assert(index >= 0 && index <= _length);
        return _string[index];
    }

    inline String &operator+=(const String &rhs) {
        _length += rhs._length;
        char *old_str = _string;
        _string = new char[_length + 1];
        strcpy(_string, old_str);
        delete[] old_str;
        strcat(_string, rhs._string);
        return *this;
    }

    inline String &operator+=(const char *rhs) {
        _length += strlen(rhs);
        char *old_str = _string;
        _string = new char[_length + 1];
        strcpy(_string, old_str);
        delete[] old_str;
        strcat(_string, rhs);
        return *this;
    }

    inline String &operator=(const String &str) {
        if (this != &str) {
            if (_length < str._length) {
                delete[] _string;
                _string = new char[str._length + 1];
            }
            _length = str._length;
            strcpy(_string, str._string);
        }
        return *this;
    }

    inline String &operator=(const char *str) {
        size_t str_len = strlen(str);
        if (_length < str_len) {
            delete[] _string;
            _string = new char[str_len + 1];
        }
        _length = str_len;
        strcpy(_string, str);
        return *this;
    }

    inline String operator+(const String &rhs) {
        String str;
        str._length = _length + rhs._length;
        str._string = new char[str._length + 1];
        strcpy(str._string, _string);
        strcat(str._string, rhs._string);
        return str;
    }

    inline String operator+(const char *rhs) {
        String str;
        str._length = _length + strlen(rhs);
        str._string = new char[str._length + 1];
        strcpy(str._string, _string);
        strcat(str._string, rhs);
        return str;
    }

    inline bool operator==(const String &rhs) {
        return strcmp(_string, rhs._string) == 0;
    }

    inline bool operator!=(const String &rhs) {
        return strcmp(_string, rhs._string) != 0;
    }

    inline bool operator<(const String &rhs) {
        return strcmp(_string, rhs._string) < 0;
    }

    inline bool operator<=(const String &rhs) {
        return strcmp(_string, rhs._string) <= 0;
    }

    inline bool operator>(const String &rhs) {
        return strcmp(_string, rhs._string) > 0;
    }

    inline bool operator>=(const String &rhs) {
        return strcmp(_string, rhs._string) >= 0;
    }

    inline bool operator==(const char *rhs) {
        return strcmp(_string, rhs) == 0;
    }

    inline bool operator!=(const char *rhs) {
        return strcmp(_string, rhs) != 0;
    }

    inline bool operator<(const char *rhs) {
        return strcmp(_string, rhs) < 0;
    }

    inline bool operator<=(const char *rhs) {
        return strcmp(_string, rhs) <= 0;
    }

    inline bool operator>(const char *rhs) {
        return strcmp(_string, rhs) > 0;
    }

    inline bool operator>=(const char *rhs) {
        return strcmp(_string, rhs) >= 0;
    }

    inline static char *int2String(int num, char *str = new char[16], int radix = 10) {

        char index[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";//索引表
        unsigned unum;//存放要转换的整数的绝对值,转换的整数可能是负数
        int i = 0, j, k;//i用来指示设置字符串相应位，转换之后i其实就是字符串的长度；转换后顺序是逆序的，有正负的情况，k用来指示调整顺序的开始位置;j用来指示调整顺序时的交换。
        //获取要转换的整数的绝对值

        if (radix == 10 && num < 0)//要转换成十进制数并且是负数
        {
            unum = (unsigned) -num;//将num的绝对值赋给unum
            str[i++] = '-';//在字符串最前面设置为'-'号，并且索引加1
        } else unum = (unsigned) num;//若是num为正，直接赋值给unum

        //转换部分，注意转换后是逆序的
        do {
            str[i++] = index[unum % (unsigned) radix];//取unum的最后一位，并设置为str对应位，指示索引加1
            unum /= radix;//unum去掉最后一位

        } while (unum);//直至unum为0退出循环

        str[i] = '\0';//在字符串最后添加'\0'字符，c语言字符串以'\0'结束。

        //将顺序调整过来
        if (str[0] == '-') k = 1;//如果是负数，符号不用调整，从符号后面开始调整
        else k = 0;//不是负数，全部都要调整

        char temp;//临时变量，交换两个值时用到
        for (j = k; j <= (i - 1) / 2; j++)//头尾一一对称交换，i其实就是字符串的长度，索引最大值比长度少1
        {
            temp = str[j];//头部赋值给临时变量
            str[j] = str[i - 1 + k - j];//尾部赋值给头部
            str[i - 1 + k - j] = temp;//将临时变量的值(其实就是之前的头部值)赋给尾部
        }

        return str;//返回转换后的字符串
    }

    inline const char *toString() {
        return _string;
    }

    unsigned int hashCode() {
        unsigned int hash = 5381;
        char *key = _string;

        while (*key) {
            hash = ((hash << 5) + hash) + (*key++); /* times 33 */
        }
        hash &= ~(1 << 31); /* strip the highest bit */
        return hash;
    }
};


#endif //SIMPLE_PYVM_STRING_HPP
