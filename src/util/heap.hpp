//
// Created by euraxluo on 2020/11/25.
//

#ifndef SIMPLE_PYVM_HEAP_HPP
#define SIMPLE_PYVM_HEAP_HPP
class Heap {
private:
    int *_tree;//数组
    int _len;//堆中已经存储的数据个数
    int _capacity;//堆的最大容量
    void heapify(int *_tree, int cur, int _len) {//up-to-bottom
        while (true) {
            int minPos = cur;
            int left = 2 * cur + 1;
            int right = 2 * cur + 2;
            int father = (cur - 1) / 2;
            //父节点
            if (father >= 0 && _tree[cur] < _tree[father])
                minPos = father;
            //左子节点
            if (left < _len && _tree[minPos] > _tree[left])
                minPos = left;
            //右子节点
            if (right < _len && _tree[minPos] > _tree[right])
                minPos = right;
            if (minPos == cur) break;
            swap(_tree[cur], _tree[minPos]);
            cur = minPos;
        }
    }

public:
    Heap(int capacity, int *tree) {//初始化
        this->_capacity = capacity;
        if (tree) this->_tree =tree;
        else this->_tree = new int[_capacity];
        this->_len = 0;
    }

    void insert(int data) {//插入数据并堆化
        if (_len >= _capacity) return;//如果堆
        int cur = _len;
        _tree[_len++] = data;//从0的位置开始存
        //bottom-to-up堆化,比较并交换当前节点和它的父节点
        heapify(_tree, cur, _len);
    }

    void remove(int pos = 0) {
        if (_len == 0) return;//堆中没有数据
        _tree[pos] = _tree[--_len];//删除堆顶元素
        heapify(_tree, pos, _len);
    }

    int len() {
        return this->_len;
    }

    int capacty() {
        return this->_capacity;
    }

    int *heap() {
        return _tree;
    }
    int top(){
        return _tree[0];
    }
};

#endif //SIMPLE_PYVM_HEAP_HPP
