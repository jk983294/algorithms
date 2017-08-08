#ifndef MYSET_H
#define MYSET_H

#include <iostream>
#include <queue>
#include <string>
#include "tree/RedBlackTree.h"

using namespace std;

template <typename Type>
class MySet {
    RBTree<Type>* tree;
    int count;

public:
    MySet();
    ~MySet();
    bool add(const Type& key);
    bool contains(const Type& key);
    bool remove(const Type& key);
    bool isEmpty();
    int size();
    void clear();
    Type* toArray(int& i);
};
template <typename Type>
MySet<Type>::MySet() {
    tree = new RBTree<Type>();
    count = 0;
}
template <typename Type>
MySet<Type>::~MySet() {
    if (tree != nullptr) {
        delete tree;
        tree = nullptr;
    }
}
template <typename Type>
bool MySet<Type>::contains(const Type& key) {
    RBNode<Type>* node = tree->rb_search(key);
    if (node == tree->nil) {
        return false;
    }
    return true;
}
template <typename Type>
bool MySet<Type>::add(const Type& key) {
    if (contains(key)) {
        return false;
    }
    RBNode<Type>* node = new RBNode<Type>(key);
    tree->rb_insert(node);
    count++;
    return true;
}
template <typename Type>
bool MySet<Type>::remove(const Type& key) {
    RBNode<Type>* node = tree->rb_search(key);
    if (node == tree->nil) {
        return false;
    }
    RBNode<Type>* result = tree->rb_delete(node);
    delete result;
    count--;
    return true;
}
template <typename Type>
bool MySet<Type>::isEmpty() {
    return count == 0;
}
template <typename Type>
int MySet<Type>::size() {
    return count;
}
template <typename Type>
void MySet<Type>::clear() {
    if (tree != nullptr) {
        delete tree;
        tree = nullptr;
    }
    tree = new RBTree<Type>();
    count = 0;
}
template <typename Type>
Type* MySet<Type>::toArray(int& i) {
    Type* a = new Type[count];
    tree->in_order(tree->root, a);
    i = count;
    return a;
}

#endif
