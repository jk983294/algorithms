#ifndef MAXHEAP_H
#define MAXHEAP_H
/**堆
MaxHeap 最大堆实现最大优先队列
*/
#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include <queue>
#include<algorithm>
#include<cmath>
using namespace std;

const int MaxN = 999;

template <class T>
class MaxHeap{
public:
    MaxHeap(){size = 0;}       //0号元素完全二叉树不用
    void insertKey(T key);
    bool deleteKey(T &ret); //删除的值放在ret中，返回值说明是否成功，堆中无数据返回false
    void print(){
        for(int i=1;i<=size;i++){cout<<heap[i]<<" ";}
        cout<<endl;
    };
public:
    int size;   //size = heap.size() -1  0号元素完全二叉树不用
    T heap[MaxN];
};
template <class T>
void MaxHeap<T>::insertKey(T key){
    size++;
    heap[size] = key;
    int pos = size;
    while(pos>1){
        if(key>heap[pos/2]){
            heap[pos] = heap[pos/2];    pos /= 2;
        }
        else break;
    }
    heap[pos] = key;
}
template <class T>
bool MaxHeap<T>::deleteKey(T &ret){
    ret= heap[0];
    bool isSuccess = false;
    if(size > 0){
        isSuccess = true;
        ret = heap[1];    //get root
        T k = heap[size--];
        int pos = 1,child = 2;  //左子女
        while(child <= size){
            if(child < size){//两个子女
                if(heap[child] < heap[child+1]) child++;    //child为较大的子女
            }
            if(k >= heap[child]) break;     //find k's place
            else{
                heap[pos] = heap[child];    //较大子女向上移
                pos = child;    child *= 2;
            }
        }
        heap[pos] = k;
    }
    return isSuccess;
}


void test_MaxHeap(){
    MaxHeap<int> h;
    int ret;
    h.insertKey(2);
    h.insertKey(3);
    h.insertKey(7);
    h.insertKey(5);
    h.insertKey(6);
    h.insertKey(9);
    h.print();

    h.deleteKey(ret);
    h.deleteKey(ret);
    h.deleteKey(ret);
    h.deleteKey(ret);
    h.deleteKey(ret);
    h.deleteKey(ret);
    h.deleteKey(ret);
    h.print();


}

#endif
