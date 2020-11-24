//
// Created by euraxluo on 2020/11/25.
//

#ifndef SIMPLE_PYVM_VECTOR_HPP
#define SIMPLE_PYVM_VECTOR_HPP

#include <string.h>
#include <assert.h>
template <typename T>
class Vector{
private:
    T* data;
    int capacity;//存储数组中可以容纳的最大的元素个数
    int size;//存储数组中的元素个数
    void resize(int newCapacity){
        assert( newCapacity >= size );
        T *newData = new T[newCapacity];
        for (int i = 0;i<size;i++)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
public:
    MyVector(){
        data = new T(10);//初始分配10个空间
        capacity = 10;
        size = 0;
    }
    ~MyVector(){//析构函数
        delete[] data;
    }
    void push_back(T e){
        assert( size < capacity );
        if(size == capacity)
            resize(2*capacity);
        data[size++] = e;
    }
    T pop_back(){
        assert( size > 0 );
        T ret = data[size-1];
        size --;
        if(size == capacity/4)//防止复杂度震荡，如果删除和添加都在11处，且这里判定条件是capacity/2
            resize(capacity/2);
        return ret;
    }
};


#endif //SIMPLE_PYVM_VECTOR_HPP
