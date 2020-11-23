//
// Created by euraxluo on 2020/11/23.
//

#ifndef PYTHONVM_ARRAYLIST_HPP
#define PYTHONVM_ARRAYLIST_HPP

template<typename T>
class ArrayList {
private:
private:
    int _length;//元素数组大小
    T *_array;//泛型指针,指向元素数组
    int _size;//用于显示当前列表中的有效元素个数

    /**
     * 在hpp中可以将模板类的实现和定义放在一起
     * 分开实现：
     * 定义：void expand();
     * 实现：template<typename T> void ArrayList<T>::expand(){}
     * 一起实现：如下
     */
    template<typename T>
    void expand() {
        /**
         * 当有效元素数量超过元素数组的容量时，可以扩展数组
         */
        T *new_array = new T[_length << 1];//_length*2
        for (int i = 0; i < _length; ++i) {
            new_array[i] = _array[i];
        }
        _array = new_array;
        delete[] _array;
        _length <<= 1;
        printf("expand an array to %d,size is %d\n", _length, _size);
    }

public:
    template<typename T>
    ArrayList(int n = 8) {
        _length = n;
        _size = 0;
        _array = new T[n];
    }

    template<typename T>
    void add(T t) {
        /**
         * 向列表的末尾添加元素
         */
        if (_size >= _length) {
            expand();
        }
        _array[_size++] = t;
    }

    template<typename T>
    void insert(int index, T t) {
        /**
         * 向指定的位置插入元素
         */
        add(NULL);//添加到末尾
        for (int i = _size; i > index; i--) {
            _array[i] = _array[i - 1];
        }
        _array[index] = t;

    }

    template<typename T>
    T get(int index) {
        return _array[index];
    }

    template<typename T>
    void set(int index, T t) {
        if (_size <= index) {
            _size = index + 1;
        }
        while (_size > _length) {
            expand();
        }
        _array[index] = t;
    }

    template<typename T>
    int size() {
        return _size;
    }

    template<typename T>
    int length() {
        return _length;
    }

    template<typename T>
    T pop() {
        return _array[--_size];
    }
};


#endif //PYTHONVM_ARRAYLIST_HPP
