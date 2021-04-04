//
// Created by euraxluo on 2020/11/22.
//

#ifndef PYTHONVM_BUFFEREDINPUTSTREAM_HPP
#define PYTHONVM_BUFFEREDINPUTSTREAM_HPP

#include <stdio.h>
#include <cstring>

#define BUFFER_LEN 256
const int MAX_LEN = BUFFER_LEN * sizeof(char);
class BufferedInputStream {
private:
    FILE *fp;//定义一个FILE 结构体类型的指针，FILE 是stdio中的一个结构体
    char szBuffer[BUFFER_LEN];
    unsigned short int index;//0-65535
    char *rootPath = nullptr;
    static BufferedInputStream *_instance;

public:
    BufferedInputStream() {}
    static BufferedInputStream* getInstance() {
        if (_instance == nullptr) {
            _instance = new BufferedInputStream();
        }
        return _instance;
    }

    void readFileName(char const *filename) {
        char *filepath = get_filename((char *) filename);
        if (*filepath == '\000' && rootPath != nullptr && *rootPath != '\000') {
            char * split = const_cast<char *>("/\000");
            rootPath = strcat(rootPath, split);
            filename = strcat(rootPath, filename);
        }
        if (rootPath == nullptr) {
            rootPath = filepath;
        }

        //file 是一个指向char const 的指针，可以改变指针的指向，但是不能改变它的值

        fp = fopen(filename, "rb");
        if (!fp){
            printf("%s\n",rootPath);
            printf("file %s not found\n", filename);
            throw "fread Exception\n";
        }
        fread(szBuffer, MAX_LEN, 1, fp);

        index = 0;
    }

    ~BufferedInputStream() {//析构函数
        close();
    }

    char read() {
        if (index < BUFFER_LEN) {
            return szBuffer[index++];
        } else {
            index = 0;
            //char,-127~128,8bit
            fread(szBuffer, BUFFER_LEN * sizeof(char), 1, fp);//读取BUFFER_LEN长的字节,并存到szBUffer中,index为0
            return szBuffer[index++];
        }
    }

    int read_int() {
        /**
         * 先转为无符号int型,再移位,避免溢出
         */
        int b1 = toUnsignedInt(read());//oxff = 11111111,简单来说会把高24位全部变成0，低8位保持不变!
        int b2 = toUnsignedInt(read());
        int b3 = toUnsignedInt(read());
        int b4 = toUnsignedInt(read());
        return b4 << 24 | b3 << 16 | b2 << 8 | b1;
    }

    double read_double() {
        char t[8];
        for (int i = 0; i < 8; i++) {
            t[i] = read();
        }
        return *(double *) t;
    }

    void unread() {
        index--;
    }

    int toUnsignedInt(char x) {
        return ((int) x) & 0xff;//将高24位全部变成0，低8位保持不变
    }

    void close() {
        if (fp != nullptr) {
            fclose(fp);
            fp = nullptr;
        }
    }

    char *get_filename(char *path) {
        int i, j = 0;
        for (i = 0; path[i]; i++) {
            if (path[i] == '/')
                j = i;
        }

        char *name = new char[j + 1];
        memcpy(name, path, j);
        return name;
    }

};


#endif //PYTHONVM_BUFFEREDINPUTSTREAM_HPP
