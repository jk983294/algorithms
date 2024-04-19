#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <tuple>
#include "BinaryTree.h"

template <class T>
class BinarySearchTree : public BinaryTree<T> {
public:
    void insert(T key);  // 有序插入
    TreeNode<T> *search(T key);
    // 删叶节点或只有一个子女的节点很容易，如果删带两个子女的节点，采取将左树最大节点或者右树最小节点代替被删节点
    bool deleteKey(T key);
    // 合并两棵有序树，左树key全部小于右树，左树最大节点为根，返回树根节点指针
    TreeNode<T> *TwoWayJoin(TreeNode<T> *left, TreeNode<T> *right);
    // predecessor and successor for a given key
    std::pair<TreeNode<T> *, TreeNode<T> *> findPreSuc(TreeNode<T> *root, T key) {
        TreeNode<T> *pre = nullptr;
        TreeNode<T> *suc = nullptr;

        while (true) {
            if (root == nullptr) return {pre, suc};
            if (root->data == key) {
                if (root->left != nullptr) {
                    auto *tmp = root->left;
                    while (tmp->right) tmp = tmp->right;
                    pre = tmp;
                }

                if (root->right != nullptr) {
                    auto *tmp = root->right;
                    while (tmp->left) tmp = tmp->left;
                    suc = tmp;
                }
                return {pre, suc};
            }

            if (root->data > key) {
                suc = root;
                root = root->left;
            } else {
                pre = root;
                root = root->right;
            }
        }
    }
};

template <class T>
TreeNode<T> *BinarySearchTree<T>::TwoWayJoin(TreeNode<T> *left, TreeNode<T> *right) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;
    TreeNode<T> *t = left;
    TreeNode<T> *p = t;            // p是t的双亲
    while (t->right != nullptr) {  // 找左子树最大节点
        p = t;
        t = p->right;
    }
    if (t->data == left->data) {  // 左子树没有右子树，直接将right拼接到他的右数
        left->right = right;
        return left;
    } else {
        p->right = nullptr;  // 最大节点从left树上取下来
        t->left = left;
        t->right = right;
        return t;
    }
}
template <class T>
bool BinarySearchTree<T>::deleteKey(T key) {  // 如果删带两个子女的节点，采取将左树最大节点代替被删节点
    TreeNode<T> *t = BinaryTree<T>::root;
    TreeNode<T> *p = t;                      // p是t的双亲
    if ((t != nullptr) && t->data == key) {  // 删除的是根节点
        BinaryTree<T>::root = TwoWayJoin(t->left, t->right);
        delete t;
        return true;
    }

    while (t != nullptr) {
        if (key == t->data) {
            // find key
            break;
        }
        if (key < t->data) {
            p = t;
            t = p->left;
        } else {
            p = t;
            t = p->right;
        }
    }
    if (t == nullptr)
        return false;
    else if ((t->left == nullptr) && (t->right == nullptr)) {  // 要删除的是叶子节点
        if (key < p->data) {                                   // p的左儿子
            p->left = nullptr;
            delete t;
        } else {
            p->right = nullptr;
            delete t;
        }
    } else if ((t->left != nullptr) && (t->right == nullptr)) {  // 要删除的只有左儿子
        if (key < p->data) {                                     // p的左儿子
            p->left = t->left;
            delete t;
        } else {
            p->right = t->left;
            delete t;
        }
    } else if ((t->left == nullptr) && (t->right != nullptr)) {  // 要删除的只有右儿子
        if (key < p->data) {                                     // p的左儿子
            p->left = t->right;
            delete t;
        } else {
            p->right = t->right;
            delete t;
        }
    } else {                  // 要删除的有左右儿子，找到左树上的最大值
        if (key < p->data) {  // p的左儿子
            p->left = TwoWayJoin(t->left, t->right);
            delete t;
        } else {
            p->right = TwoWayJoin(t->left, t->right);
            delete t;
        }
    }
    return true;
}
template <class T>
TreeNode<T> *BinarySearchTree<T>::search(T key) {
    TreeNode<T> *t = BinaryTree<T>::root;
    while (t != nullptr) {
        if (key == t->data) {
            return t;
        }
        if (key < t->data)
            t = t->left;
        else
            t = t->right;
    }
    return nullptr;
}
template <class T>
void BinarySearchTree<T>::insert(T x) {
    bool isSuccess = true;
    if (BinaryTree<T>::root == nullptr) {
        BinaryTree<T>::root = new TreeNode<T>(x);
    } else {
        TreeNode<T> *current = BinaryTree<T>::root;
        TreeNode<T> *next = BinaryTree<T>::root;
        do {
            current = next;
            if (current->data < x) {
                next = current->right;
            } else if (current->data > x) {
                next = current->left;
            } else {
                isSuccess = false;
            }
        } while (next != nullptr);  // find leaf
        if (current->data < x) {
            current->right = new TreeNode<T>(x);
        } else if (current->data > x) {
            current->left = new TreeNode<T>(x);
        }
    }
    if (isSuccess) {
        BinaryTree<T>::size++;
    }
}

#endif
