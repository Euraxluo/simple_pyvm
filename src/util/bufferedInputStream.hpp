//
// Created by euraxluo on 2020/11/22.
//

#ifndef PYTHONVM_BUFFEREDINPUTSTREAM_HPP
#define PYTHONVM_BUFFEREDINPUTSTREAM_HPP

#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <climits>
#include <stdlib.h>
#include <iostream>

#define BUFFER_LEN 256
const int MAX_LEN = BUFFER_LEN * sizeof(char);

class BufferedInputStream {
private:
    FILE *fp;//定义一个FILE 结构体类型的指针，FILE 是stdio中的一个结构体
    char szBuffer[BUFFER_LEN];
    unsigned short int index;//0-65535
    char *rootPath = nullptr;
    char *workPath = nullptr;
    size_t dirPathSize = 0;
    char **dirPath = nullptr;
    static BufferedInputStream *_instance;

public:
    BufferedInputStream() {}

    static BufferedInputStream *getInstance() {
        if (_instance == nullptr) {
            _instance = new BufferedInputStream();
        }
        return _instance;
    }

    void addDirPath(char *dirpath) {
        dirPathSize++;
        char **old = dirPath;
        dirPath = new char *[dirPathSize];
        for (int i = 0; i < dirPathSize - 1; ++i) {
            dirPath[i] = old[i];
        }
        dirPath[dirPathSize - 1] = dirpath;
    }

    void readFileName(char const *filename) {
        char *tmp = nullptr;
        if (dirPathSize == 0) {
            char abs_path_buff[PATH_MAX];
            if (realpath(".", abs_path_buff)) {
                tmp = abs_path_buff;
                addDirPath(tmp);
            } else {
                throw "realpath Exception when get workPath\n";
            }

            char *filepath = getpath((char *) filename);
            addDirPath(filepath);
        }

        //1.先直接读取文件
        tmp = const_cast<char *>(filename);
        if (access(tmp, R_OK) != 0) {
            for (int i = 0; i < dirPathSize; ++i) {
                if (dirPath[i] != "") {
                    tmp = new char[PATH_MAX];
                    char * split = const_cast<char *>("/\000");
                    strcpy(tmp,dirPath[i]);
                    tmp = strcat(tmp, split);
                    tmp = strcat(tmp, filename);
                }

                if (access(tmp, R_OK) == 0)
                    break;
                delete tmp;
            }
        }

        fp = fopen(tmp, "rb");
        if (!fp) {
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

    char *getpath(char *filename) {
        int i, j = 0;
        for (i = 0; filename[i]; i++) {
            if (filename[i] == '/')
                j = i;
        }

        char *name = new char[j + 1];
        memcpy(name, filename, j);
        return name;
    }

};


#endif //PYTHONVM_BUFFEREDINPUTSTREAM_HPP
