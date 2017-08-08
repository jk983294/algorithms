#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

using namespace std;

/**
 * MaxHeap 最大堆实现最大优先队列
 */

static const int MaxN = 999;

template <class T>
class MaxHeap {
public:
    MaxHeap() {
        size = 0;  // 0号元素完全二叉树不用
        heap.resize(MaxN);
    }
    void insertKey(T key);
    bool deleteKey(T &ret);  // 删除的值放在ret中，返回值说明是否成功，堆中无数据返回false
    void print() {
        for (int i = 1; i <= size; i++) {
            cout << heap[i] << ", ";
        }
        cout << endl;
    };

public:
    int size;  // size = heap.size() -1  0号元素完全二叉树不用
    vector<T> heap;
};
template <class T>
void MaxHeap<T>::insertKey(T key) {
    size++;
    heap[size] = key;
    int pos = size;
    while (pos > 1) {
        if (key > heap[pos / 2]) {
            heap[pos] = heap[pos / 2];
            pos /= 2;
        } else
            break;
    }
    heap[pos] = key;
}
template <class T>
bool MaxHeap<T>::deleteKey(T &ret) {
    ret = heap[0];
    bool isSuccess = false;
    if (size > 0) {
        isSuccess = true;
        ret = heap[1];  // get root
        T k = heap[size--];
        int pos = 1, child = 2;  // 左子女
        while (child <= size) {
            if (child < size) {                              // 两个子女
                if (heap[child] < heap[child + 1]) child++;  // child为较大的子女
            }
            if (k >= heap[child])
                break;  // find k's place
            else {
                heap[pos] = heap[child];  // 较大子女向上移
                pos = child;
                child *= 2;
            }
        }
        heap[pos] = k;
    }
    return isSuccess;
}

#endif
