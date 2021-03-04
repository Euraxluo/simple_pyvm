//
// Created by euraxluo on 2020/11/23.
//

#ifndef PYTHONVM_ARRAYLIST_HPP
#define PYTHONVM_ARRAYLIST_HPP

#include <assert.h>
//typedef
typedef __SIZE_TYPE__ size_t;

template<typename T>
class ArrayList {
private:
    size_t _capacity;//元素数组大小
    T *_array;//泛型指针,指向元素数组
    size_t _size;//用于显示当前列表中的有效元素个数
    /**
     * 在hpp中可以将模板类的实现和定义放在一起
     * 分开实现：
     * 定义：void expand();
     * 实现：template<typename T> void ArrayList<T>::expand(){}
     * 一起实现：如下
     */
    void resize(int capacity) {
        assert(capacity >= _size);
        T *new_array = new T[capacity];
        for (int i = 0; i < _size; i++)
            new_array[i] = _array[i];
        delete[] _array;
        _array = new_array;
        _capacity = capacity;
    }

public:
    //int 构造器
    ArrayList(size_t capacity = 0) {
        if (capacity>0){
            _capacity = capacity;
            _size = 0;
            _array = new T[_capacity];
        } else{
            _capacity = 1;
            _size = 0;
            _array = new T[_capacity];
        }
    }
//    ArrayList(){
//        _capacity=1;
//        _size=0;
//        _array = new T[_capacity];
//    }

//    ArrayList(const T *array){
//        _size = 0;
//        if (array){
//
//        }
//    }

    ~ArrayList() {
        delete[] _array;
    }

    void push(T t) {
        /**
         * 将元素放到ArrayList的末尾
         */
        assert(_size <= _capacity);
        if (_size == _capacity) {
            resize(_capacity << 1);
        }
        _array[_size++] = t;
    }

    T pop() {
        /**
         * 移除ArrayList的最后一个元素
         */
        assert(_size > 0);
        T back = _array[--_size];
        if (_size == _capacity >> 2) {
            if (_capacity == 1)
                return back;
            resize(_capacity >> 1);
        }
        return back;
    }

    void insert(int index, T t) {
        /**
         * 向指定的位置插入元素
         */
        push(0);//添加一个元素到末尾
        for (int i = _size; i > index; i--) {
            _array[i] = _array[i - 1];
        }
        _array[index] = t;
    }

    void remove(int index){
        /**
         * 移除指定位置的元素
         */
        if (index<0){
            index = size()+index;
        }
        if (index<_size){
            for (int i = index; i < _size; i++) {
                _array[i] = _array[i+1];
            }
            pop();
        }

    }

    T get(int index=-1) {
        /**
         * 获取指定索引的数据
         */
        if(index==-1) index = (_size-1);
        assert(index<_size);
        return _array[index];
    }

    void set(int index, T t) {
        /**
         * 设置指定索引的数据
         */
        if (_size <= index) {
            _size = index + 1;
        }
        if (_size > _capacity) {
            resize(index<<1);
        }
        _array[index] = t;
    }

    int size() {
        /**
         * 返回有效元素数量
         */
        return _size;
    }

    int capacity() {
        /**
         * 元素数组的容量
         */
        return _capacity;
    }

    int length() {
        /**
         * 元素数组的长度
         */
        return _capacity;
    }

    //重载
    inline char &operator[](const size_t index) {
        assert(index >= 0 && index <= _size);
        return _array[index];
    }
};

#endif //PYTHONVM_ARRAYLIST_HPP
