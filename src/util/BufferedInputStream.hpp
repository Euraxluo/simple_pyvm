//
// Created by euraxluo on 2020/11/22.
//

#ifndef PYTHONVM_BUFFEREDINPUTSTREAM_HPP
#define PYTHONVM_BUFFEREDINPUTSTREAM_HPP

#include <stdio.h>
#define BUFFER_LEN 256

class BufferedInputStream {
private:
    FILE* fp;//定义一个FILE 结构体类型的指针，FILE 是stdio中的一个结构体
    char szBuffer[BUFFER_LEN];
    unsigned short int index;//0-65535
public:
    BufferedInputStream(char const* filename){//构造函数
        //file 是一个指向char const 的指针，可以改变指针的指向，但是不能改变它的值
        fp = fopen(filename,"rb");
        fread(szBuffer,BUFFER_LEN* sizeof(char),1,fp);
        index=0;
    }
    ~BufferedInputStream() {//析构函数
        close();
    }

    void close(){
        if (fp!=NULL){
            fclose(fp);
            fp = NULL;
        }
    }

};


#endif //PYTHONVM_BUFFEREDINPUTSTREAM_HPP
