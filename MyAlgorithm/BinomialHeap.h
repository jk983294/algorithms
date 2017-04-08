#ifndef BINOMIALHEAP_H
#define BINOMIALHEAP_H
/**堆
最小堆实现
支持O(lgn)时间合并两个堆
*/
#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include <queue>
#include<algorithm>
#include<cmath>
using namespace std;

template <class T>
class BiHeapNode{
public:
    T key;
    BiHeapNode<T> *p, *child, *sibling;   //parent  最左孩子  紧邻右兄弟
    int degree;     //子女个数
public:
    BiHeapNode(){   p=child=sibling=NULL; };
    BiHeapNode(T newkey){ key = newkey; p=child=sibling=NULL; degree=0; };
};
template <class T>
ostream& operator<<(ostream& os, BiHeapNode<T>* n){
    os<<n->key<<"_";
    if(n->p!=NULL){os<<n->p->key;}
    else{os<<"nil";}
    return os;
}

template <class T>
class MinBinomialHeap{
public:
    int size;
    BiHeapNode<T> *head;
public:
    MinBinomialHeap(){size = 0;     head = NULL;}
    ~MinBinomialHeap(){clear();};
    void clear();
    bool empty(){ return size>0?false:true;};
    void union_heap(BiHeapNode<T> *h2);  //h2合并到this
    void union_heap(MinBinomialHeap<T> &h2);  //h2合并到this
    BiHeapNode<T> *minimum();   //找heap中最下元素节点，没有返回NULL
    void insertKey(T key);
    bool deleteMin(T &ret); //删除的值放在ret中，堆中无数据返回false,遍历根节点即可O(lgn)
    bool deleteKey(T key);  //删除任意key节点
    BiHeapNode<T> * findNode(T key);       //返回key在heap中的位置
    bool decrease_key(T oldkey, T newkey);    //修改oldkey为newkey  修改完后调maintainHeap,向上冒泡O(lgn)
    void print();
private:
    void link(BiHeapNode<T> *y, BiHeapNode<T> *z);  //将以y为根的B(k-1)树与以z为根的B(k-1)树合并为以z为根的B(k)树
    BiHeapNode<T> * merge(BiHeapNode<T> *h1,BiHeapNode<T> *h2); //根表按degree顺序排序

};
template <class T>
BiHeapNode<T>* MinBinomialHeap<T>::merge(BiHeapNode<T> *h1,BiHeapNode<T> *h2){
    if(h1==NULL)    return h2;
    else if(h2==NULL)   return h1;
    else{
        BiHeapNode<T> *newhead=NULL, *x=NULL;
        if(h1->degree <= h2->degree){  newhead=h1;   h1=h1->sibling;  }
        else{  newhead=h2;   h2=h2->sibling; }
        x = newhead;
        while((h1!=NULL) && (h2!=NULL)){
            if(h1->degree <= h2->degree){  x->sibling=h1;  x=h1; h1=h1->sibling;  }
            else{  x->sibling=h2;  x=h2; h2=h2->sibling; }
        }
        if(h1!=NULL){  x->sibling=h1; }
        if(h2!=NULL){  x->sibling=h2; }
        return newhead;
    }
}
template <class T>
void MinBinomialHeap<T>::union_heap(MinBinomialHeap<T> &h2){
    union_heap(h2.head);    size += h2.size;
    h2.head = NULL; h2.size = 0;
}
template <class T>
void MinBinomialHeap<T>::union_heap(BiHeapNode<T> *h2){
    head = merge(head,h2);      //根表按degree顺序排序
    if(head == NULL){ return;}
    BiHeapNode<T> *pre_x=NULL, *x = head, *next_x = x->sibling;
    while(next_x !=NULL){
        if((x->degree != next_x->degree)   || ( (next_x->sibling!=NULL)  && (next_x->sibling->degree == x->degree))){
            //case 1 and case 2
            pre_x = x;  x=next_x;
        }
        else if(x->key  <= next_x->key){
            //case 3: next_x becames x's leftest child, so head is not change
            x->sibling = next_x->sibling;
            link(next_x,x);
        }
        else {  //下面都是x->key  > next_x->key的情况
            if(pre_x == NULL){  head = next_x;}
            else{   pre_x->sibling = next_x;}
            link(x,next_x);
            x = next_x;
        }
        next_x = x->sibling;
    }
}
template <class T>
void MinBinomialHeap<T>::link(BiHeapNode<T> *y, BiHeapNode<T> *z){
    y->p = z;
    y->sibling = z->child;
    z->child = y;
    z->degree ++;
}
template <class T>
BiHeapNode<T>* MinBinomialHeap<T>::minimum(){
    if(empty()) return NULL;
    BiHeapNode<T> *y, *x=head;  //y记录最小值的节点指针
    T min = x->key; y=x;  x=x->sibling;
    while(x!=NULL){
        if(x->key < min){
            min = x->key;  y=x;
        }
        x=x->sibling;
    }
    return y;
}
template <class T>
bool MinBinomialHeap<T>::deleteKey(T key){
    BiHeapNode<T> *x,*y,*z,*nextx,*prex,*prey; T tmp;
    x = findNode(key);
    if(x==NULL )    return false;
    else{
        //将该节点调整到根表中去,节点为y,z为y的父亲
        y=x;    z=y->p;
        while(z!=NULL){
            tmp = y->key; y->key = z->key;    z->key = tmp;
            y=z;    z= y->p;
        }
        //在根表中找到该节点的前驱prey
        x=head; prey=NULL;
        while(x!=NULL){
            if( x== y){ break;}
            prey = x; x=x->sibling;
        }
        ///需要断开 y
        if(prey == NULL){  head = y->sibling;   y->sibling = NULL;}
        else{   prey->sibling = NULL;   union_heap(y->sibling); y->sibling = NULL;}//除y以外部分形成一个二项堆
        //反转y的child链表  链首保持在x中
        x = y->child;   prex = NULL;
        while(x!=NULL){
            if(prex == NULL){   x->p = NULL; prex= x; x=x->sibling; prex->sibling = NULL;}
            else{
                x->p = NULL;    nextx = x->sibling;     x->sibling = prex;
                if(nextx == NULL)   break;
                else{  prex= x; x=x->sibling; }
            }
        }
        x = (x==NULL)?prex:x;
        union_heap(x);
        size--;
        delete y;
        return true;
    }
}
template <class T>
bool MinBinomialHeap<T>::deleteMin(T &min){
    if(empty()) return false;
    BiHeapNode<T> *y, *x=head,*nextx,*prex,*prey;  //y记录最小值的节点指针
    min = x->key; y=prey = prex=NULL;
    while(x!=NULL){
        if(x->key <= min){
            min = x->key; prey = prex; y=x;
        }
        prex = x; x=x->sibling;
    }

    ///delete y //需要断开 y
    if(prey == NULL){  head = y->sibling;   y->sibling = NULL;} //最小元素为第一个元素
    else{   prey->sibling = NULL;   union_heap(y->sibling); y->sibling = NULL;}//除y以外部分形成一个二项堆
    //反转y的child链表  链首保持在x中
    x = y->child;   prex = NULL;
    while(x!=NULL){
        if(prex == NULL){   x->p = NULL; prex= x; x=x->sibling; prex->sibling = NULL;}
        else{
            x->p = NULL;    nextx = x->sibling;     x->sibling = prex;
            if(nextx == NULL)   break;
            else{  prex= x; x=x->sibling; }
        }
    }
    x = (x==NULL)?prex:x;
    union_heap(x);
    size--;
    delete y;
    return true;
}
template <class T>
void MinBinomialHeap<T>::insertKey(T key){
    BiHeapNode<T> *x = new BiHeapNode<T>(key);
    union_heap(x);
    size++;
}
template <class T>
BiHeapNode<T> * MinBinomialHeap<T>::findNode(T key){
    queue<BiHeapNode<T> *> q;   //有child的入栈
    BiHeapNode<T> *x=head;
    q.push(x);
    while(!q.empty()){
        x = q.front();    q.pop();
        while(x!=NULL) {
            if(x->key == key){  return x; }
            if(x->child != NULL)   {    q.push(x->child);  }
            x=x->sibling;
        }
    }
    return NULL;
}
template <class T>
bool MinBinomialHeap<T>::decrease_key(T oldkey, T newkey){
    if(oldkey <= newkey)    return false;
    BiHeapNode<T> *x,*y,*z;
    x = findNode(oldkey);
    if(x==NULL )    return false;
    else{
        x->key = newkey;    y=x;    z=y->p;
        while( (z!=NULL) && (y->key < z->key)){
            T tmp = y->key; y->key = z->key;    z->key = tmp;
            y=z;    z= y->p;
        }
    }
}
template <class T>
void MinBinomialHeap<T>::clear(){
    queue<BiHeapNode<T> *> q;   //有child的入栈
    BiHeapNode<T> *x=head,*y;
    q.push(x);
    while(!q.empty()){
        x = q.front();    q.pop();
        while(x!=NULL) {
            if(x->child != NULL)   {    q.push(x->child);  }
            y=x;    x=x->sibling;
            delete y;
        }
    }
    head = NULL;    size = 0;
}
template <class T>
void MinBinomialHeap<T>::print(){
    cout<<size<<" nodes: "<<endl;
    queue<BiHeapNode<T> *> q;   //有child的入栈
    BiHeapNode<T> *x=head;
    q.push(x);
    while(!q.empty()){
        x = q.front();    q.pop();
        while(x!=NULL) {
            cout<<x<<" ";
            if(x->child != NULL)   {    q.push(x->child);  }
            x=x->sibling;
        }
        cout<<endl;
    }
    cout<<endl;
}




void test_BinomialHeap(){
    MinBinomialHeap<int> h;
    h.clear();
    cout<<"after clear(): "<<endl;
    h.print();

    int ret,index;
    h.insertKey(9);
    h.print();
    h.insertKey(2);
    h.print();
    h.insertKey(3);
    h.print();
    h.insertKey(7);
    h.print();
    h.insertKey(5);
    h.print();
    h.insertKey(6);
    h.print();

    h.deleteKey(9);
    h.print();

    h.deleteMin(ret);
    h.print();
    h.deleteMin(ret);
    h.print();
    h.deleteMin(ret);
    h.print();



    h.insertKey(9);
    h.print();
    h.insertKey(2);
    h.print();
    h.insertKey(3);
    h.print();


    h.clear();
    cout<<"after clear(): "<<endl;
    h.print();

    h.insertKey(7);
    h.print();
    h.insertKey(5);
    h.print();
    h.insertKey(6);
    h.print();

    cout<<"end"<<endl;
}

#endif
