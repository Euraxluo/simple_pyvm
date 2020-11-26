//
// Created by euraxluo on 2020/11/24.
// test pass
//

#ifndef PYTHONVM_HISTRING_HPP
#define PYTHONVM_HISTRING_HPP

#include "Object.hpp"
#include <assert.h>

class String : public Object {
private:
    char *_string;
    size_t _length;

    inline char *strcpy(char *dst, const char *src) {
        char *ret = dst;
        memcpy(dst, src, strlen(src) + 1);
        return ret;
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

    inline int strcmp(const char *str1, const char *str2){
        while(*str1 && (*str1==*str2)){
            ++str1;
            ++str2;
        }
        return *str1 - *str2;
    }

public:
    //初始化列表
    String(){
        _length=0;
        _string = new char[1];
        _string[_length] = '\0';
    }

    //char* 构造器
    String(const char *str) {
        _length = 0;
        if (str) {
            _length = strlen(str);
            _string = new char[_length + 1];
            strcpy(_string, str);
        }
        _string[_length] = '\0';
    }

    //char* 构造器，但是可以指定长度,注意这里不要超出了字符的长度，否则会cpy到其他内存区
    String(const char *x, size_t length) {
        _length = length;
        _string = new char[length];
        memcpy(_string, x, _length);
    }

    String(const size_t times, const char ch) {
        _length = times;
        _string = new char[_length + 1];
        *(_string + _length) = '\0';
        strset(_string, ch);
    }

    //拷贝构造
    String(const String &str) {
        _length = str._length;
        _string = new char[_length + 1];
        strcpy(_string, str._string);
    }

    ~String() {
        delete[] _string;
    }
        printf("~String");

    inline const char *c_str() {
        return _string;
    }

    inline size_t length() {
        return _length;
    }

    inline bool empty() {
        return _length == 0 ? true : false;
    }

    inline char **c_addr() {
        return &_string;
    }
    inline  String& append(const String& str){
        *this+=str;//重载
        return *this;
    }
    inline  String& append(const char* str){
        _length += strlen(str);
        char * old_str = _string;
        _string = new char[_length + 1];
        strcpy(_string,old_str);
        delete[] old_str;
        strcat(_string,str);
        return *this;
    }

    /**以下是重载运算符*/
    inline char &operator[](const size_t index) {
        assert(index >= 0 && index <= _length);
        return _string[index];
    }

    inline String &operator+=(const String &rhs) {
        _length += rhs._length;
        char * old_str = _string;
        _string = new char[_length + 1];
        strcpy(_string,old_str);
        delete[] old_str;
        strcat(_string,rhs._string);
        return *this;
    }
    inline String &operator+=(const char * rhs) {
        _length += strlen(rhs);
        char * old_str = _string;
        _string = new char[_length + 1];
        strcpy(_string,old_str);
        delete[] old_str;
        strcat(_string,rhs);
        return *this;
    }

    inline String& operator=(const String& str){
        if (this!=&str){
            if (_length<str._length){
                delete[] _string;
                _string = new char[str._length+1];
            }
            _length = str._length;
            strcpy(_string,str._string);
        }
        return *this;
    }

    inline String& operator=(const char * str){
        size_t str_len=strlen(str);
        if (_length<str_len){
            delete[] _string;
            _string = new char[str_len+1];
        }
        _length = str_len;
        strcpy(_string,str);
        return *this;
    }

    inline String operator+(const String &rhs){
        String str;
        str._length = _length+rhs._length;
        str._string = new char[str._length+1];
        strcpy(str._string,_string);
        strcat(str._string,rhs._string);
        return str;
    }

    inline String operator+(const char * rhs){
        String str;
        str._length = _length+strlen(rhs);
        str._string = new char[str._length+1];
        strcpy(str._string,_string);
        strcat(str._string,rhs);
        return str;
    }

    inline bool operator==(const String& rhs){
        return strcmp(_string,rhs._string)==0;
    }
    inline bool operator!=(const String& rhs){
        return strcmp(_string,rhs._string)!=0;
    }
    inline bool operator<(const String& rhs){
        return strcmp(_string,rhs._string)<0;
    }
    inline bool operator<=(const String& rhs){
        return strcmp(_string,rhs._string)<=0;
    }
    inline bool operator>(const String& rhs){
        return strcmp(_string,rhs._string)>0;
    }
    inline bool operator>=(const String& rhs){
        return strcmp(_string,rhs._string)>=0;
    }

    inline bool operator==(const char * rhs){
        return strcmp(_string,rhs)==0;
    }
    inline bool operator!=(const char * rhs){
        return strcmp(_string,rhs)!=0;
    }
    inline bool operator<(const char * rhs){
        return strcmp(_string,rhs)<0;
    }
    inline bool operator<=(const char * rhs){
        return strcmp(_string,rhs)<=0;
    }
    inline bool operator>(const char * rhs){
        return strcmp(_string,rhs)>0;
    }
    inline bool operator>=(const char * rhs){
        return strcmp(_string,rhs)>=0;
    }
};



#endif //PYTHONVM_HISTRING_HPP
