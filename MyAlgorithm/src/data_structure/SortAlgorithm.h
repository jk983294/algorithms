#ifndef SORT_ALGORITHM_H
#define SORT_ALGORITHM_H

#include "utilities.h"

using namespace std;

/**
 * 排序, 按照从小到大的顺序
 */
template <class T>
class SortAlgorithm {
public:
    SortAlgorithm(T *data, int n) {
        this->n = n;
        this->data = data;
    };

    ~SortAlgorithm(){};

    inline void swap(int i, int j) {
        T tmp = data[i];
        data[i] = data[j];
        data[j] = tmp;
    };
    void insertSort();                    // 插入排序
    void shellSort();                     // 希尔排序, 减少增量排序
    void quickSort(int left, int right);  // 快排
    void bubbleSort();                    // 冒泡排序
    void heapSort();                      // 堆排序
    void mergeSort();                     // 归并排序
    bool binarySearch(T key);             // 二分查找
    int binarySearchForIndex(T key);      // 二分查找, 返回下标, -1表示没找到

    void print() {
        for (int u = 0; u < n; u++) {
            cout << data[u] << " ";
        }
        cout << endl;
    };

public:
    T *data;  // 数据指针
    int n;    // 排序元素个数 from [0...n-1]
};
template <class T>
void SortAlgorithm<T>::insertSort() {
    T key;
    int pos;
    for (int i = 1; i < n; i++) {  // 前[0 ... i-1]已经排序好
        key = data[i];
        pos = i - 1;
        while ((pos >= 0) && (key < data[pos])) {
            data[pos + 1] = data[pos];
            pos--;
        }
        data[pos + 1] = key;
    }
}
template <class T>
void SortAlgorithm<T>::shellSort() {
    int incr = n;  // 增量
    T key;
    int pos;
    do {
        incr = incr / 3 + 1;
        for (int start = 0; start < incr; start++) {  // 对每个子表进行排序
            for (int j = start; j < n; j += incr) {   // 子表中每个元素进行插入排序
                key = data[j];
                pos = j - incr;
                while ((pos >= 0) && (key < data[pos])) {
                    data[pos + incr] = data[pos];
                    pos -= incr;
                }
                data[pos + incr] = key;
            }
        }
    } while (incr > 1);  // 最后一遍的增量为1，变成插入排序
}
template <class T>
void SortAlgorithm<T>::quickSort(int left, int right) {  // [left, right]
    if (left < right) {
        int i = left, j = right + 1, pivot = data[left];
        do {
            do {
                i++;
            } while (i <= right && data[i] < pivot);
            do {
                j--;
            } while (j >= left && data[j] > pivot);
            if (i < j) swap(i, j);
        } while (i < j);
        swap(left, j);
        quickSort(left, j - 1);
        quickSort(j + 1, right);
    }
}
template <class T>
void SortAlgorithm<T>::bubbleSort() {
    for (int i = 0; i < n - 1; i++) {  // 每轮做完后，最大的元素沉到最后面data[n-1-i]位置
        for (int j = 0; j < n - i - 1; j++) {
            if (data[j] > data[j + 1])  // 每次比较相邻的两个元素
                swap(j, j + 1);
        }
    }
}
template <class T>
void SortAlgorithm<T>::heapSort() {
    make_heap(data, data + n);  // 默认最大堆
    sort_heap(data, data + n);  // 默认从小到大
}
template <class T>
bool SortAlgorithm<T>::binarySearch(T key) {
    int left = 0, right = n - 1;
    int middle = (left + right) / 2;
    while (left <= right) {
        if (data[middle] == key)
            return true;
        else if (data[middle] < key)
            left = middle + 1;
        else if (data[middle] > key)
            right = middle - 1;
        middle = (left + right) / 2;
    }
    return false;
}
template <class T>
int SortAlgorithm<T>::binarySearchForIndex(T key) {
    int left = 0, right = n - 1, middle;
    while (left <= right) {
        middle = (left + right) / 2;
        if (data[middle] == key)
            return middle;
        else if (data[middle] < key)
            left = middle + 1;
        else
            right = middle - 1;
    }
    return -1;
}

#endif
