#ifndef BINOMIALHEAP_H
#define BINOMIALHEAP_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

using namespace std;

/**
 * 最小堆实现
 * 支持O(lgn)时间合并两个堆
 */

template <class T>
class BiHeapNode {
public:
    T key;
    BiHeapNode<T> *p, *child, *sibling;  // parent  最左孩子  紧邻右兄弟
    int degree;                          // 子女个数
public:
    BiHeapNode() { p = child = sibling = nullptr; };
    BiHeapNode(T newKey) {
        key = newKey;
        p = child = sibling = nullptr;
        degree = 0;
    };
};
template <class T>
ostream &operator<<(ostream &os, BiHeapNode<T> *n) {
    os << n->key << "_";
    if (n->p != nullptr) {
        os << n->p->key;
    } else {
        os << "nil";
    }
    return os;
}

template <class T>
class MinBinomialHeap {
public:
    int size;
    BiHeapNode<T> *head;

public:
    MinBinomialHeap() {
        size = 0;
        head = nullptr;
    }
    ~MinBinomialHeap() { clear(); };
    void clear();
    bool empty() { return size <= 0; };
    void union_heap(BiHeapNode<T> *h2);       // h2合并到this
    void union_heap(MinBinomialHeap<T> &h2);  // h2合并到this
    BiHeapNode<T> *minimum();                 // 找heap中最下元素节点，没有返回nullptr
    void insertKey(T key);
    bool deleteMin(T &ret);  // 删除的值放在ret中，堆中无数据返回false,遍历根节点即可O(lgn)
    bool deleteKey(T key);   // 删除任意key节点
    BiHeapNode<T> *findNode(T key);         // 返回key在heap中的位置
    bool decrease_key(T oldKey, T newKey);  // 修改oldKey为newKey  修改完后调maintainHeap,向上冒泡O(lgn)
    void print();

private:
    void link(BiHeapNode<T> *y, BiHeapNode<T> *z);  // 将以y为根的B(k-1)树与以z为根的B(k-1)树合并为以z为根的B(k)树
    BiHeapNode<T> *merge(BiHeapNode<T> *h1, BiHeapNode<T> *h2);  // 根表按degree顺序排序
};
template <class T>
BiHeapNode<T> *MinBinomialHeap<T>::merge(BiHeapNode<T> *h1, BiHeapNode<T> *h2) {
    if (h1 == nullptr)
        return h2;
    else if (h2 == nullptr)
        return h1;
    else {
        BiHeapNode<T> *newhead = nullptr, *x = nullptr;
        if (h1->degree <= h2->degree) {
            newhead = h1;
            h1 = h1->sibling;
        } else {
            newhead = h2;
            h2 = h2->sibling;
        }
        x = newhead;
        while ((h1 != nullptr) && (h2 != nullptr)) {
            if (h1->degree <= h2->degree) {
                x->sibling = h1;
                x = h1;
                h1 = h1->sibling;
            } else {
                x->sibling = h2;
                x = h2;
                h2 = h2->sibling;
            }
        }
        if (h1 != nullptr) {
            x->sibling = h1;
        }
        if (h2 != nullptr) {
            x->sibling = h2;
        }
        return newhead;
    }
}
template <class T>
void MinBinomialHeap<T>::union_heap(MinBinomialHeap<T> &h2) {
    union_heap(h2.head);
    size += h2.size;
    h2.head = nullptr;
    h2.size = 0;
}
template <class T>
void MinBinomialHeap<T>::union_heap(BiHeapNode<T> *h2) {
    head = merge(head, h2);  // 根表按degree顺序排序
    if (head == nullptr) {
        return;
    }
    BiHeapNode<T> *pre_x = nullptr, *x = head, *next_x = x->sibling;
    while (next_x != nullptr) {
        if ((x->degree != next_x->degree) || ((next_x->sibling != nullptr) && (next_x->sibling->degree == x->degree))) {
            // case 1 and case 2
            pre_x = x;
            x = next_x;
        } else if (x->key <= next_x->key) {
            // case 3: next_x become x's leftest child, so head is not change
            x->sibling = next_x->sibling;
            link(next_x, x);
        } else {  // 下面都是x->key  > next_x->key的情况
            if (pre_x == nullptr) {
                head = next_x;
            } else {
                pre_x->sibling = next_x;
            }
            link(x, next_x);
            x = next_x;
        }
        next_x = x->sibling;
    }
}
template <class T>
void MinBinomialHeap<T>::link(BiHeapNode<T> *y, BiHeapNode<T> *z) {
    y->p = z;
    y->sibling = z->child;
    z->child = y;
    z->degree++;
}
template <class T>
BiHeapNode<T> *MinBinomialHeap<T>::minimum() {
    if (empty()) return nullptr;
    BiHeapNode<T> *y, *x = head;  // y记录最小值的节点指针
    T min = x->key;
    y = x;
    x = x->sibling;
    while (x != nullptr) {
        if (x->key < min) {
            min = x->key;
            y = x;
        }
        x = x->sibling;
    }
    return y;
}
template <class T>
bool MinBinomialHeap<T>::deleteKey(T key) {
    BiHeapNode<T> *x, *y, *z, *nextX, *preX, *preY;
    T tmp;
    x = findNode(key);
    if (x == nullptr)
        return false;
    else {
        // 将该节点调整到根表中去,节点为y,z为y的父亲
        y = x;
        z = y->p;
        while (z != nullptr) {
            tmp = y->key;
            y->key = z->key;
            z->key = tmp;
            y = z;
            z = y->p;
        }
        // 在根表中找到该节点的前驱preY
        x = head;
        preY = nullptr;
        while (x != nullptr) {
            if (x == y) {
                break;
            }
            preY = x;
            x = x->sibling;
        }
        // 需要断开 y
        if (preY == nullptr) {
            head = y->sibling;
            y->sibling = nullptr;
        } else {
            preY->sibling = nullptr;
            union_heap(y->sibling);
            y->sibling = nullptr;
        }  // 除y以外部分形成一个二项堆
        // 反转y的child链表  链首保持在x中
        x = y->child;
        preX = nullptr;
        while (x != nullptr) {
            if (preX == nullptr) {
                x->p = nullptr;
                preX = x;
                x = x->sibling;
                preX->sibling = nullptr;
            } else {
                x->p = nullptr;
                nextX = x->sibling;
                x->sibling = preX;
                if (nextX == nullptr)
                    break;
                else {
                    preX = x;
                    x = x->sibling;
                }
            }
        }
        x = (x == nullptr) ? preX : x;
        union_heap(x);
        size--;
        delete y;
        return true;
    }
}
template <class T>
bool MinBinomialHeap<T>::deleteMin(T &min) {
    if (empty()) return false;
    BiHeapNode<T> *y, *x = head, *nextX, *preX, *preY;  // y记录最小值的节点指针
    min = x->key;
    y = preY = preX = nullptr;
    while (x != nullptr) {
        if (x->key <= min) {
            min = x->key;
            preY = preX;
            y = x;
        }
        preX = x;
        x = x->sibling;
    }

    // delete y //需要断开 y
    if (preY == nullptr) {
        head = y->sibling;
        y->sibling = nullptr;
    }  // 最小元素为第一个元素
    else {
        preY->sibling = nullptr;
        union_heap(y->sibling);
        y->sibling = nullptr;
    }  // 除y以外部分形成一个二项堆
    // 反转y的child链表  链首保持在x中
    x = y->child;
    preX = nullptr;
    while (x != nullptr) {
        if (preX == nullptr) {
            x->p = nullptr;
            preX = x;
            x = x->sibling;
            preX->sibling = nullptr;
        } else {
            x->p = nullptr;
            nextX = x->sibling;
            x->sibling = preX;
            if (nextX == nullptr)
                break;
            else {
                preX = x;
                x = x->sibling;
            }
        }
    }
    x = (x == nullptr) ? preX : x;
    union_heap(x);
    size--;
    delete y;
    return true;
}
template <class T>
void MinBinomialHeap<T>::insertKey(T key) {
    BiHeapNode<T> *x = new BiHeapNode<T>(key);
    union_heap(x);
    size++;
}
template <class T>
BiHeapNode<T> *MinBinomialHeap<T>::findNode(T key) {
    queue<BiHeapNode<T> *> q;  // 有child的入栈
    BiHeapNode<T> *x = head;
    q.push(x);
    while (!q.empty()) {
        x = q.front();
        q.pop();
        while (x != nullptr) {
            if (x->key == key) {
                return x;
            }
            if (x->child != nullptr) {
                q.push(x->child);
            }
            x = x->sibling;
        }
    }
    return nullptr;
}
template <class T>
bool MinBinomialHeap<T>::decrease_key(T oldKey, T newKey) {
    if (oldKey <= newKey) return false;
    BiHeapNode<T> *x, *y, *z;
    x = findNode(oldKey);
    if (x == nullptr)
        return false;
    else {
        x->key = newKey;
        y = x;
        z = y->p;
        while ((z != nullptr) && (y->key < z->key)) {
            T tmp = y->key;
            y->key = z->key;
            z->key = tmp;
            y = z;
            z = y->p;
        }
    }
}
template <class T>
void MinBinomialHeap<T>::clear() {
    queue<BiHeapNode<T> *> q;  // 有child的入栈
    BiHeapNode<T> *x = head, *y;
    q.push(x);
    while (!q.empty()) {
        x = q.front();
        q.pop();
        while (x != nullptr) {
            if (x->child != nullptr) {
                q.push(x->child);
            }
            y = x;
            x = x->sibling;
            delete y;
        }
    }
    head = nullptr;
    size = 0;
}
template <class T>
void MinBinomialHeap<T>::print() {
    cout << size << " nodes: " << endl;
    queue<BiHeapNode<T> *> q;  // 有child的入栈
    BiHeapNode<T> *x = head;
    q.push(x);
    while (!q.empty()) {
        x = q.front();
        q.pop();
        while (x != nullptr) {
            cout << x << " ";
            if (x->child != nullptr) {
                q.push(x->child);
            }
            x = x->sibling;
        }
        cout << endl;
    }
    cout << endl;
}

#endif
