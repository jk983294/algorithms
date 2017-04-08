#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H

//带头结点的单链表
template<class T>
class SingleListNode {
public:
    SingleListNode(T &n) {
        this->val = n;
        this->next = NULL;
    };
    SingleListNode(){};
    T val;
    SingleListNode *next;
};
template<class T>
class slist {
public:
    slist();
    ~slist();
    void push_front(T &t);
    bool find(T &t);
    bool remove(T &t);
    bool removeAll(T &t);
    void clear();
    int size();
public:
    int m_nListDataCount;
    SingleListNode<T> *m_head;
};
template<class T>
slist<T>::slist() {
    m_head = NULL;
    m_nListDataCount = 0;
}
template<class T>
slist<T>::~slist() {
    SingleListNode<T> *p, *pNext;
    for (p = m_head; p != NULL; p = pNext) {
        pNext = p->next;
        delete p;
    }
    m_nListDataCount = 0;
}
template<class T>
void slist<T>::push_front(T &t) {
    SingleListNode<T> *pSingleListNode = new SingleListNode<T>();
    pSingleListNode->val = t;
    pSingleListNode->next = m_head;
    m_head = pSingleListNode;
    m_nListDataCount++;
}
template<class T>
bool slist<T>::find(T &t) {
    for (SingleListNode<T> *p = m_head; p != NULL; p = p->next)
        if (p->val == t)
            return true;

    return false;
}
template<class T>
int slist<T>::size() {
    return m_nListDataCount;
}
//删除链表中第一个值为t的结点
template<class T>
bool slist<T>::remove(T &t)
{
    SingleListNode<T> *pSingleListNode, *pPreSingleListNode;
    pPreSingleListNode = pSingleListNode = m_head;
    while (pSingleListNode != NULL) {
        if (pSingleListNode->val == t) {
            if (pPreSingleListNode != pSingleListNode)
                pPreSingleListNode->next = pSingleListNode->next;
            else
                m_head = NULL;
            delete pSingleListNode;
            m_nListDataCount--;
            return true;
        }
        pPreSingleListNode = pSingleListNode;
        pSingleListNode = pSingleListNode->next;
    }
    return false;
}
//会删除链表中所有值为t的结点
template<class T>
bool slist<T>::removeAll(T &t) {
    bool flagDeleteSingleListNode = false;
    SingleListNode<T> *pSingleListNode, *pPreSingleListNode;
    pPreSingleListNode = pSingleListNode = m_head;
    while (pSingleListNode != NULL) {
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
template<class T>
void slist<T>::clear() {
    SingleListNode<T> *cur = m_head;
    while (cur != NULL) {
        SingleListNode<T> *next = cur->next;
        delete cur;
        cur = next;
    }
    m_head = NULL;
}

#endif
