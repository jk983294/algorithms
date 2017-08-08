#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include "SingleList.h"

using namespace std;

/**
 * 使用链表法解决hash碰撞
 */
template <class T, class container = vector<SingleList<T> > >
class hash_table {
public:
    hash_table();
    hash_table(const unsigned int table_size);
    ~hash_table();
    void clear();
    bool insert(T &n);                 // 当m_nDataCount>m_nTableSize时自动扩容
    void insert(T *pFirst, T *pLast);  // 插入数组区域
    bool erase(T &n);
    void resize(unsigned int nNewTableSize);
    bool find(T &n);
    unsigned int size();
    unsigned int HashFun(T &n);  // hash function
    void StatisticHashTable();   // 统计每个slot上有多少数据，计算平均slot长度
private:
    static unsigned int findNextPrime(unsigned int curPrime);

public:
    unsigned int m_nDataCount;
    unsigned int m_nTableSize;
    container m_Table;
    static const unsigned int m_primes[50];
};
// 素数表
template <class T, class container>
const unsigned int hash_table<T, container>::m_primes[50] = {
    53,     97,     193,    389,     769,     1453,    3079,     6151,     1289,     24593,     49157,    98317,
    196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319, 201326611};
template <class T, class container>
unsigned int inline hash_table<T, container>::HashFun(T &n) {
    return (n ^ 0xdeadbeef) % m_nTableSize;  // 按位异或
}
template <class T, class container>
hash_table<T, container>::hash_table() {
    m_nDataCount = 0;
    m_nTableSize = m_primes[0];
    m_Table.resize(m_nTableSize);
}
template <class T, class container>
hash_table<T, container>::hash_table(const unsigned int table_size) {
    m_nDataCount = 0;
    m_nTableSize = table_size;
    m_Table.resize(m_nTableSize);
}
template <class T, class container>
hash_table<T, container>::~hash_table() {
    clear();
}
template <class T, class container>
void hash_table<T, container>::clear() {
    for (unsigned int i = 0; i < m_nTableSize; i++) m_Table[i].clear();
    m_nDataCount = 0;
}
template <class T, class container>
bool hash_table<T, container>::insert(T &n) {
    unsigned int key = HashFun(n);
    if (!m_Table[key].find(n)) {
        m_nDataCount++;
        m_Table[key].push_front(n);  // 头插法
        if (m_nDataCount >= m_nTableSize) resize(findNextPrime(m_nTableSize));
    }
    return true;
}
template <class T, class container>
bool hash_table<T, container>::erase(T &n) {
    unsigned int key = HashFun(n);
    if (m_Table[key].remove(n)) {
        m_nDataCount--;
        return true;
    } else {
        return false;
    }
}
template <class T, class container>
void hash_table<T, container>::insert(T *pFirst, T *pLast) {
    for (T *p = pFirst; p != pLast; p++) this->insert(*p);
}
template <class T, class container>
void hash_table<T, container>::resize(unsigned int nNewTableSize) {
    if (nNewTableSize <= m_nTableSize) return;
    unsigned int nOldTableSize = m_nTableSize;
    m_nTableSize = nNewTableSize;
    container tempTable(m_nTableSize);                  // 创建一个更大的表
    for (unsigned int i = 0; i < nOldTableSize; i++) {  // 将原表中数据重新插入到新表中
        SingleListNode<T> *cur = m_Table[i].m_head;
        while (cur != nullptr) {
            unsigned int key = HashFun(cur->val);
            SingleListNode<T> *pNext = cur->next;
            cur->next = tempTable[key].m_head;
            tempTable[key].m_head = cur;
            cur = pNext;
        }
        m_Table[i].m_head = nullptr;
    }
    m_Table.swap(tempTable);
}
template <class T, class container>
unsigned int hash_table<T, container>::size() {
    return m_nDataCount;
}
template <class T, class container>
bool hash_table<T, container>::find(T &n) {
    unsigned int key = HashFun(n);
    return m_Table[key].find(n);
}
// 在素数表中找到比当前数大的最小数
template <class T, class container>
unsigned int hash_table<T, container>::findNextPrime(unsigned int curPrime) {
    unsigned int *pStart = (unsigned int *)m_primes;
    while (*pStart <= curPrime) ++pStart;
    return *pStart;
}
template <class T, class container>
void hash_table<T, container>::StatisticHashTable() {
    const unsigned int MAX_LIST_LINE = 100;
    unsigned int i, nExtendListNum;
    vector<int> a(MAX_LIST_LINE, 0);
    nExtendListNum = 0;
    for (i = 0; i < m_nTableSize; i++) {
        unsigned int sum = m_Table[i].size();
        if (sum >= MAX_LIST_LINE)
            nExtendListNum++;
        else
            a[sum]++;
    }
    cout << "hash_table list length statistics: " << endl;
    for (i = 0; i < MAX_LIST_LINE; i++) {
        if (a[i] > 0)
            cout << "there are " << a[i] << " lists with length " << i
                 << ". the data count ratio against whole data count is " << (a[i] * i * 100.0) / m_nDataCount << " %"
                 << endl;
    }
    cout << "there are " << nExtendListNum << " lists with exceeding length " << MAX_LIST_LINE << endl;
}

#endif
