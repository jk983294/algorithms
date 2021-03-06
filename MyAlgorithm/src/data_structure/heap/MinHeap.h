#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

using namespace std;

/**
 * MinHeap 最小堆实现最大优先队列
 */

static const int MaxN = 999;

template <class T>
class MinHeap {
public:
    MinHeap() {
        size = 0;  // 0号元素完全二叉树不用
        heap.resize(MaxN);
    }
    void clear() { size = 0; };
    bool empty() { return size <= 0; };
    void insertKey(T key);
    bool deleteKey(T &ret);  // 删除的值放在ret中，返回值说明是否成功，堆中无数据返回false
    int findItem(T key);     // 返回key在heap中的位置下标
    bool changeItem(int index, T key);               // 修改heap[index]数据为key  修改完后调maintainHeap
    void maintainHeap(bool isNewBigger, int index);  // heap[index]数据修改后维护堆结构

    void print() {
        for (int i = 1; i <= size; i++) {
            cout << heap[i] << ", ";
        }
        cout << endl;
    }

public:
    int size;  // size = heap.size() -1  0号元素完全二叉树不用
    vector<T> heap;
};
template <class T>
void MinHeap<T>::maintainHeap(bool isNewBigger, int index) {  // heap[index]修改过，需要维护heap结构
    T tmp;
    int leftchild, rightchild;
    if (isNewBigger) {  // isNewBigger=true,新插入数据比原来的数据大，向下调整
        while (index < size) {
            leftchild = index * 2;
            rightchild = leftchild + 1;
            if (leftchild > size) {
                break;
            }                               // 该节点没有儿子了
            else if (rightchild <= size) {  // 有两个儿子
                if ((heap[index] <= heap[leftchild]) && (heap[index] <= heap[rightchild])) {
                    break;
                } else if ((heap[index] > heap[leftchild]) &&
                           (heap[index] <= heap[rightchild])) {  // 比左边的大，比右边的小，沿着左向下沉
                    tmp = heap[index];
                    heap[index] = heap[leftchild];
                    heap[leftchild] = tmp;
                    index = leftchild;
                } else if ((heap[index] <= heap[leftchild]) &&
                           (heap[index] > heap[rightchild])) {  // 比左边的小，比右边的大，沿着右向下沉
                    tmp = heap[index];
                    heap[index] = heap[rightchild];
                    heap[rightchild] = tmp;
                    index = rightchild;
                } else {  // 比左边、右边都大，沿着子女中较小的沉
                    int minIndex = (heap[leftchild] < heap[rightchild]) ? leftchild : rightchild;
                    tmp = heap[index];
                    heap[index] = heap[minIndex];
                    heap[minIndex] = tmp;
                    index = minIndex;
                }
            } else {  // 只有一个左儿子
                if (heap[index] <= heap[leftchild]) {
                    break;
                } else {  // 比左边的大,沿着左向下沉
                    tmp = heap[index];
                    heap[index] = heap[leftchild];
                    heap[leftchild] = tmp;
                    index = leftchild;
                }
            }
        }
    } else {  // isNewBigger=false,新插入数据比原来的数据小，向上调整
        while (index > 1) {
            if (heap[index] < heap[index / 2]) {  // 自己比父亲小，需要上移
                tmp = heap[index];
                heap[index] = heap[index / 2];
                heap[index / 2] = tmp;
                index /= 2;
            } else
                break;
        }
    }
}
template <class T>
bool MinHeap<T>::changeItem(int index, T key) {
    if (index > 0) {
        bool isNewBigger = (key > heap[index]);
        heap[index] = key;
        maintainHeap(isNewBigger, index);
        return true;
    } else
        return false;
}
template <class T>
int MinHeap<T>::findItem(T key) {
    for (int i = 1; i <= size; i++) {
        if (key == heap[i]) return i;
    }
    return -1;
}
template <class T>
void MinHeap<T>::insertKey(T key) {
    size++;
    heap[size] = key;
    int pos = size;
    while (pos > 1) {
        if (key < heap[pos / 2]) {
            heap[pos] = heap[pos / 2];
            pos /= 2;
        } else
            break;
    }
    heap[pos] = key;
}
template <class T>
bool MinHeap<T>::deleteKey(T &ret) {
    ret = heap[0];
    bool isSuccess = false;
    if (size > 0) {
        isSuccess = true;
        ret = heap[1];  // get root
        T k = heap[size--];
        int pos = 1, child = 2;  // 左子女
        while (child <= size) {
            if (child < size) {                              // 两个子女
                if (heap[child] > heap[child + 1]) child++;  // child为较小的子女
            }
            if (k <= heap[child])
                break;  // find k's place
            else {
                heap[pos] = heap[child];  // 较小子女向上移
                pos = child;
                child *= 2;
            }
        }
        heap[pos] = k;
    }
    return isSuccess;
}

#endif
