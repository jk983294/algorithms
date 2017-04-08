#ifndef MYSET_H
#define MYSET_H

#include <string>
#include <iostream>
#include <queue>
#include "RedBlackTree.h"

using namespace std;

template <typename Type>
class MySet{
    RBTree<Type>* tree;
    int count;
public:
    MySet();
    ~MySet();
    bool add(const Type& key);
    bool contains(const Type& key);
    bool remove(const Type& key);
    bool isEmpty();
    int  size();
    void clear();
    Type* toArray(int& i);
};
template <typename Type>
MySet<Type>::MySet(){
    tree=new RBTree<Type>();
    count=0;
}
template <typename Type>
MySet<Type>::~MySet(){
    if(tree!=NULL){
        delete tree;
        tree=NULL;
    }
}
template <typename Type>
bool MySet<Type>::contains(const Type& key){
    TNode<Type>* node=tree->rb_search(key);
    if(node==tree->nil){
        return false;
    }
    return true;
}
template <typename Type>
bool MySet<Type>::add(const Type& key){
    if(contains(key)){
        return false;
    }
    TNode<Type>* node=new TNode<Type>(key);
    tree->rb_insert(node);
    count++;
    return true;
}
template <typename Type>
bool MySet<Type>::remove(const Type& key){
    TNode<Type>* node=tree->rb_search(key);
    if(node==tree->nil){
        return false;
    }
    TNode<Type>* result=tree->rb_delete(node);
    delete result;
    count--;
    return true;
}
template <typename Type>
bool MySet<Type>::isEmpty(){
    return count==0?true:false;
}
template <typename Type>
int MySet<Type>::size(){
    return count;
}
template <typename Type>
void MySet<Type>::clear(){
    if(tree!=NULL){
        delete tree;
        tree=NULL;
    }
    tree=new RBTree<Type>();
    count=0;
}
template <typename Type>
Type* MySet<Type>::toArray(int& i){
    Type* a=new Type[count];
    tree->inorder(tree->root,a);
    i=count;
    return a;
}

void  test_MySet(){

    MySet<int>* set=new MySet<int>();
    for(int i=1000;i>0;i--){
        set->add(i);
    }
    cout<<"倒序插入1000个数之后\n";
    int count=0;
    int* a=set->toArray(count);
    cout<<"遍历较小的十个数:\n";
    for(int i=0;i<10;i++){
        cout<<a[i]<<"\t";
    }
    cout<<endl;

    set->remove(1);
    cout<<"after remove 1.set.size()="<<set->size()<<endl;

    set->clear();
    cout<<"after clear 1.set.size()="<<set->size()<<endl;
    delete set;

    getchar();

}

#endif
