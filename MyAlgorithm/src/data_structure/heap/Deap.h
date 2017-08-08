#ifndef DEAP_H
#define DEAP_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

using namespace std;

/**
 * 双堆
 */

static const int MaxN = 999;

template <class T>
class Deap {
public:
    Deap() {
        size = 0;  // 0,1号元素不用
        heap.resize(MaxN);
    }
    void insertKey(T key);
    bool isMaxHeap(int p);       // p>1  p是否是在最大堆中，还是在最小堆
    int MinPartner(int p);       // p在最大堆，找到p的最小堆对应节点
    int MaxPartner(int p);       // p在最大堆，找到p的最小堆对应节点
    void minInsert(int i, T x);  // 在最小堆的位置i,插入x,最小堆树根为1
    void maxInsert(int i, T x);  // 在最大堆的位置i,插入x,最大堆树根为2
    bool deleteMin(T &ret);      // 删除的值放在ret中，返回值说明是否成功，堆中无数据返回false
    bool deleteMax(T &ret);
    void print() {
        for (int i = 2; i <= 1 + size; i++) {
            cout << heap[i] << ", ";
        }
        cout << endl;
    };

public:
    int size;  // size = heap.size() -1  0号元素完全二叉树不用
    vector<T> heap;
};

template <class T>
void Deap<T>::insertKey(T x) {
    size++;
    if (size == 1) {
        heap[2] = x;
        return;
    }                  // first element
    int p = size + 1;  // last element pos
    int partner;
    if (isMaxHeap(p)) {  // max heap
        partner = MinPartner(p);
        if (x < heap[partner]) {  // 插入值小于最小堆对应节点，插入值扔到最小堆插入
            heap[p] = heap[partner];
            minInsert(partner, x);
        } else
            maxInsert(p, x);
    } else {  // min heap
        partner = MaxPartner(p);
        if (x > heap[partner]) {  // 插入值大于最大堆对应节点，插入值扔到最大堆插入
            heap[p] = heap[partner];
            maxInsert(partner, x);
        } else
            minInsert(p, x);
    }
}
template <class T>
bool Deap<T>::isMaxHeap(int p) {
    int level = ceil(log(p + 1) / log(2));
    if ((p < pow(2, level)) && (p >= pow(2, level) - pow(2, level - 2)))
        return true;
    else
        return false;
}
template <class T>
int Deap<T>::MinPartner(int p) {
    int level = ceil(log(p + 1) / log(2));
    return p - pow(2, level - 2);
}
template <class T>
int Deap<T>::MaxPartner(int p) {
    int level = ceil(log(p + 1) / log(2));
    if ((p + pow(2, level - 2)) <= size + 1)
        return p + pow(2, level - 2);  // 对应右子树节点存在
    else
        return (p + pow(2, level - 2)) / 2;  // 不存在，返回对应节点的双亲位置
}
template <class T>
void Deap<T>::minInsert(int i, T x) {
    int pos = i;
    while (pos > 2) {
        if (x < heap[pos / 2]) {
            heap[pos] = heap[pos / 2];
            pos /= 2;
        } else
            break;
    }
    heap[pos] = x;
}
template <class T>
void Deap<T>::maxInsert(int i, T x) {
    int pos = i;
    while (pos > 3) {
        if (x > heap[pos / 2]) {
            heap[pos] = heap[pos / 2];
            pos /= 2;
        } else
            break;
    }
    heap[pos] = x;
}
template <class T>
bool Deap<T>::deleteMin(T &ret) {
    bool isSuccess = false;
    if (size > 0) {
        ret = heap[2];
        T last = heap[size + 1];
        size--;
        int pos = 2, child = pos * 2;
        while (child <= size + 1) {                                            // 至少有一个左儿子
            if ((child + 1 >= size + 1) && (heap[child] > heap[child + 1])) {  // 有右儿子，并且右小于左
                child++;                                                       // child指向右儿子
            }
            heap[pos] = heap[child];  // 小儿子上移
            pos = child;
            child = pos * 2;
        }
        // 叶节点的pos位置插入数据last
        int partner = MaxPartner(pos);
        if (last > heap[partner]) {  // 插入值大于最大堆对应节点，插入值扔到最大堆插入
            heap[pos] = heap[partner];
            maxInsert(partner, last);
        } else
            minInsert(pos, last);
        isSuccess = true;
    }
    return isSuccess;
}
template <class T>
bool Deap<T>::deleteMax(T &ret) {
    bool isSuccess = false;
    if (size == 1) {
        ret = heap[2];
        size--;
        isSuccess = true;
    } else if (size > 1) {
        ret = heap[3];
        T last = heap[size + 1];
        size--;
        int pos = 3, child = pos * 2;
        while (child <= size + 1) {                                            // 至少有一个左儿子
            if ((child + 1 >= size + 1) && (heap[child] < heap[child + 1])) {  // 有右儿子，并且右大于左
                child++;                                                       // child指向右儿子
            }
            heap[pos] = heap[child];  // 大儿子上移
            pos = child;
            child = pos * 2;
        }
        // 叶节点的pos位置插入数据last
        int partner = MinPartner(pos);
        if (last < heap[partner]) {  // 插入值小于最小堆对应节点，插入值扔到最小堆插入
            heap[pos] = heap[partner];
            minInsert(partner, last);
        } else
            maxInsert(pos, last);
        isSuccess = true;
    }
    return isSuccess;
}

#endif
