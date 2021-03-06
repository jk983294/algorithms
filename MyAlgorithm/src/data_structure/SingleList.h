#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H

// 带头结点的单链表
template <class T>
class SingleListNode {
public:
    SingleListNode(T &n) {
        this->val = n;
        this->next = nullptr;
    };
    SingleListNode(){};
    T val;
    SingleListNode *next;
};

template <class T>
class SingleList {
public:
    SingleList();
    ~SingleList();
    void push_front(T &t);
    bool find(T &t);
    bool remove(T &t);
    bool removeAll(T &t);
    void clear();
    int size();
    SingleListNode<T> *remove_last_kth_element(int k);
    void reverse();

public:
    int m_nListDataCount;
    SingleListNode<T> *m_head;
};
template <class T>
SingleList<T>::SingleList() {
    m_head = nullptr;
    m_nListDataCount = 0;
}
template <class T>
SingleList<T>::~SingleList() {
    SingleListNode<T> *p, *pNext;
    for (p = m_head; p != nullptr; p = pNext) {
        pNext = p->next;
        delete p;
    }
    m_nListDataCount = 0;
}
template <class T>
void SingleList<T>::push_front(T &t) {
    SingleListNode<T> *pSingleListNode = new SingleListNode<T>();
    pSingleListNode->val = t;
    pSingleListNode->next = m_head;
    m_head = pSingleListNode;
    m_nListDataCount++;
}
template <class T>
bool SingleList<T>::find(T &t) {
    for (SingleListNode<T> *p = m_head; p != nullptr; p = p->next)
        if (p->val == t) return true;

    return false;
}
template <class T>
int SingleList<T>::size() {
    return m_nListDataCount;
}
// 删除链表中第一个值为t的结点
template <class T>
bool SingleList<T>::remove(T &t) {
    SingleListNode<T> *pSingleListNode, *pPreSingleListNode;
    pPreSingleListNode = pSingleListNode = m_head;
    while (pSingleListNode != nullptr) {
        if (pSingleListNode->val == t) {
            if (pPreSingleListNode != pSingleListNode)
                pPreSingleListNode->next = pSingleListNode->next;
            else
                m_head = nullptr;
            delete pSingleListNode;
            m_nListDataCount--;
            return true;
        }
        pPreSingleListNode = pSingleListNode;
        pSingleListNode = pSingleListNode->next;
    }
    return false;
}
// 会删除链表中所有值为t的结点
template <class T>
bool SingleList<T>::removeAll(T &t) {
    bool flagDeleteSingleListNode = false;
    SingleListNode<T> *pSingleListNode, *pPreSingleListNode;
    pPreSingleListNode = pSingleListNode = m_head;
    while (pSingleListNode != nullptr) {
        if (pSingleListNode->val == t) {
            pPreSingleListNode->next = pSingleListNode->next;
            delete pSingleListNode;
            pSingleListNode = pPreSingleListNode->next;
            m_nListDataCount--;
            flagDeleteSingleListNode = true;
        } else {
            pPreSingleListNode = pSingleListNode;
            pSingleListNode = pSingleListNode->next;
        }
    }
    return flagDeleteSingleListNode;
}
template <class T>
void SingleList<T>::clear() {
    SingleListNode<T> *cur = m_head;
    while (cur != nullptr) {
        SingleListNode<T> *next = cur->next;
        delete cur;
        cur = next;
    }
    m_head = nullptr;
    m_nListDataCount = 0;
}

template <class T>
SingleListNode<T> *SingleList<T>::remove_last_kth_element(int k) {
    SingleListNode<T> *result = nullptr;
    if (k <= 0 || m_nListDataCount < k)
        return nullptr;
    else if (m_nListDataCount == k) {
        result = m_head;
        m_head = m_head->next;
    } else {
        int step = m_nListDataCount - k - 1;
        SingleListNode<T> *pre = m_head;
        while (step) {
            pre = pre->next;
            --step;
        }
        result = pre->next;
        pre->next = result->next;
    }
    --m_nListDataCount;
    return result;
}

template <class T>
void SingleList<T>::reverse() {
    if (m_nListDataCount <= 1) return;
    SingleListNode<T> *pre = m_head;
    SingleListNode<T> *cur = m_head->next;
    SingleListNode<T> *next = cur->next;
    m_head->next = nullptr;
    while (cur) {
        next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    m_head = pre;
}

#endif
