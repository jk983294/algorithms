#ifndef LEFTIST_H
#define LEFTIST_H

#include "BinaryTree.h"

using namespace std;

/**左偏树 插入删除O(lgN) 合并两棵树O(lgN)
 * MaxLeftistTree  最大左偏树
 * MinLeftistTree  最小左偏树
 */

template <class T>
class LeftistNode : public TreeNode<T> {
public:
    LeftistNode(T x) : TreeNode<T>(x) { shortest = 1; }

public:
    int shortest;
};

template <class T>
class MaxLeftistTree : public BinaryTree<T> {
public:
    MaxLeftistTree() : BinaryTree<T>() { BinaryTree<T>::size = 0; }
    void insert(T data);  // 将data插入树中
    bool deleteKey(T &ret);
    void combine(MaxLeftistTree<T> &b);                  // b和*this合并
    TreeNode<T> *Union(TreeNode<T> *a, TreeNode<T> *b);  // 合并以a,b为根的两棵树
};

template <class T>
class MinLeftistTree : public BinaryTree<T> {
public:
    MinLeftistTree() : BinaryTree<T>() { BinaryTree<T>::size = 0; }
    void insert(T data);  // 将data插入树中
    bool deleteKey(T &ret);
    void combine(MinLeftistTree<T> &b);                  // b和*this合并
    TreeNode<T> *Union(TreeNode<T> *a, TreeNode<T> *b);  // 合并以a,b为根的两棵树
};

template <class T>
bool MaxLeftistTree<T>::deleteKey(T &ret) {
    bool isSuccess = false;
    if (BinaryTree<T>::root != nullptr) {
        TreeNode<T> *a = BinaryTree<T>::root;
        ret = a->data;
        BinaryTree<T>::root = Union(a->left, a->right);
        delete a;
        BinaryTree<T>::size--;
        isSuccess = true;
    }
    return isSuccess;
}
template <class T>
void MaxLeftistTree<T>::combine(MaxLeftistTree<T> &b) {
    if (BinaryTree<T>::size == 0) {
        BinaryTree<T>::root = b.root;
    } else if (b.size > 0) {
        BinaryTree<T>::root = Union(BinaryTree<T>::root, b.root);
    }
    BinaryTree<T>::size += b.size;
    b.root = nullptr;  // b树删除
    b.size = 0;
}
template <class T>
TreeNode<T> *MaxLeftistTree<T>::Union(TreeNode<T> *a, TreeNode<T> *b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;
    TreeNode<T> *tmp;
    if (a->data < b->data) {  // make sure a为大的
        tmp = a;
        a = b;
        b = tmp;
    }
    // 构建最大二叉树
    if (a->right == nullptr)
        a->right = b;
    else
        a->right = Union(a->right, b);
    // 维护左偏树性质
    if (a->left == nullptr) {  // 左树为空，交换
        a->left = a->right;
        a->right = nullptr;
    } else if (static_cast<LeftistNode<T> *>(a->left)->shortest <
               static_cast<LeftistNode<T> *>(a->right)->shortest) {  // swap
        tmp = a->left;
        a->left = a->right;
        a->right = tmp;
    }
    // set shortest
    if (a->right == nullptr)
        (static_cast<LeftistNode<T> *>(a))->shortest = 1;
    else
        (static_cast<LeftistNode<T> *>(a))->shortest = (static_cast<LeftistNode<T> *>(a->right))->shortest + 1;
    return a;
}
template <class T>
void MaxLeftistTree<T>::insert(T data) {  // 将data插入树中origin的左边或右边
    LeftistNode<T> *b = new LeftistNode<T>(data);
    MaxLeftistTree<T> tree;
    tree.root = b;
    tree.size = 1;
    combine(tree);
}

template <class T>
bool MinLeftistTree<T>::deleteKey(T &ret) {
    bool isSuccess = false;
    if (BinaryTree<T>::root != nullptr) {
        TreeNode<T> *a = BinaryTree<T>::root;
        ret = a->data;
        BinaryTree<T>::root = Union(a->left, a->right);
        delete a;
        BinaryTree<T>::size--;
        isSuccess = true;
    }
    return isSuccess;
}
template <class T>
void MinLeftistTree<T>::combine(MinLeftistTree<T> &b) {
    if (BinaryTree<T>::size == 0) {
        BinaryTree<T>::root = b.root;
    } else if (b.size > 0) {
        BinaryTree<T>::root = Union(BinaryTree<T>::root, b.root);
    }
    BinaryTree<T>::size += b.size;
    b.root = nullptr;  // b树删除
    b.size = 0;
}
template <class T>
TreeNode<T> *MinLeftistTree<T>::Union(TreeNode<T> *a, TreeNode<T> *b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;
    TreeNode<T> *tmp;
    if (a->data > b->data) {  // make sure a为小的
        tmp = a;
        a = b;
        b = tmp;
    }
    // 构建最小二叉树
    if (a->right == nullptr)
        a->right = b;
    else
        a->right = Union(a->right, b);
    // 维护左偏树性质
    if (a->left == nullptr) {  // 左树为空，交换
        a->left = a->right;
        a->right = nullptr;
    } else if (static_cast<LeftistNode<T> *>(a->left)->shortest <
               static_cast<LeftistNode<T> *>(a->right)->shortest) {  // swap
        tmp = a->left;
        a->left = a->right;
        a->right = tmp;
    }
    // set shortest
    if (a->right == nullptr)
        (static_cast<LeftistNode<T> *>(a))->shortest = 1;
    else
        (static_cast<LeftistNode<T> *>(a))->shortest = (static_cast<LeftistNode<T> *>(a->right))->shortest + 1;
    return a;
}
template <class T>
void MinLeftistTree<T>::insert(T data) {  // 将data插入树中origin的左边或右边
    LeftistNode<T> *b = new LeftistNode<T>(data);
    MinLeftistTree<T> tree;
    tree.root = b;
    tree.size = 1;
    combine(tree);
}

#endif
