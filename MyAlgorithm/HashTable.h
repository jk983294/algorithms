#ifndef HASHTABLE_H
#define HASHTABLE_H
/**
使用链表法解决hash碰撞
*/
#include <vector>
#include <iostream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include "slist.h"

using namespace std;

//slist（single linked list）单链表
//使用vector< slist<T> >为容器的hash_table
template< class T, class container = vector<slist<T> > >
class hash_table {
public:
    hash_table();
    hash_table(const int table_size);
    ~hash_table();
    void clear();
    bool insert(T &n);                  //当m_nDataCount>m_nTableSize时自动扩容
    void insert(T *pFirst, T *pLast);   //插入数组区域
    bool erase(T &n);
    void resize(int nNewTableSize);
    bool find(T &n);
    int size();
    int HashFun(T &n);      //hash function
    void StatisticHashTable();  //统计每个slot上有多少数据，计算平均slot长度
private:
    static int findNextPrime(int curPrime);
public:
    int         m_nDataCount;
    int         m_nTableSize;
    container   m_Table;
    static const unsigned int m_primes[50];
};
//素数表
template< class T, class container>
const unsigned int hash_table<T, container>::m_primes[50] = {
        53, 97, 193, 389, 769, 1453, 3079, 6151, 1289, 24593, 49157, 98317,
        196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917,
        25165843, 50331653, 100663319, 201326611
};
template< class T, class container>
int inline hash_table<T, container>::HashFun(T &n) {
    return (n ^ 0xdeadbeef) % m_nTableSize;     //按位异或
}
template< class T, class container>
hash_table<T, container>::hash_table() {
    m_nDataCount = 0;
    m_nTableSize = m_primes[0];
    m_Table.resize(m_nTableSize);
}
template< class T, class container>
hash_table<T, container>::hash_table(const int table_size) {
    m_nDataCount = 0;
    m_nTableSize = table_size;
    m_Table.resize(m_nTableSize);
}
template< class T, class container>
hash_table<T, container>::~hash_table() {
    clear();
}
template< class T, class container>
void hash_table<T, container>::clear() {
    for (int i = 0; i < m_nTableSize; i++)
        m_Table[i].clear();
    m_nDataCount = 0;
}
template< class T, class container>
bool hash_table<T, container>::insert(T &n) {
    int key = HashFun(n);
    if (!m_Table[key].find(n))
    {
        m_nDataCount++;
        m_Table[key].push_front(n);     //头插法
        if (m_nDataCount >= m_nTableSize)
            resize(findNextPrime(m_nTableSize));
    }
    return true;
}
template< class T, class container>
bool hash_table<T, container>::erase(T &n) {
    int key = HashFun(n);
    if (m_Table[key].remove(n)) {
        m_nDataCount--;
        return true;
    } else {
        return false;
    }
}
template< class T, class container>
void hash_table<T, container>::insert(T *pFirst, T *pLast) {
    for (T *p = pFirst; p != pLast; p++)
        this->insert(*p);
}
template< class T, class container>
void hash_table<T, container>::resize(int nNewTableSize) {
    if (nNewTableSize <= m_nTableSize)
        return;
    int nOldTableSize = m_nTableSize;
    m_nTableSize = nNewTableSize;
    container tempTable(m_nTableSize);             //创建一个更大的表
    for (int i = 0; i < nOldTableSize; i++) {    //将原表中数据重新插入到新表中
        SingleListNode<T> *cur = m_Table[i].m_head;
        while (cur != NULL) {
            int key = HashFun(cur->val);
            SingleListNode<T> *pNext = cur->next;
            cur->next = tempTable[key].m_head;
            tempTable[key].m_head = cur;
            cur = pNext;
        }
        m_Table[i].m_head = NULL;
    }
    m_Table.swap(tempTable);
}
template< class T, class container>
int hash_table<T, container>::size() {
    return m_nDataCount;
}
template< class T, class container>
bool hash_table<T, container>::find(T &n) {
    int key = HashFun(n);
    return m_Table[key].find(n);
}
//在素数表中找到比当前数大的最小数
template< class T, class container>
int hash_table<T, container>::findNextPrime(int curPrime) {
    unsigned int *pStart = (unsigned int *)m_primes;
    while (*pStart <= curPrime)
        ++pStart;
    //cout<<"increase size to "<<*pStart<<endl;
    return *pStart;
}
template< class T, class container>
void hash_table<T, container>::StatisticHashTable() {
    const int MAX_LIST_LINE = 100;
    int i, nExtendListNum;
    vector<int> a(MAX_LIST_LINE,0);
    nExtendListNum = 0;
    for (i = 0; i <m_nTableSize; i++) {
        int sum = m_Table[i].size();
        if (sum >= MAX_LIST_LINE)
            nExtendListNum++;
        else
            a[sum]++;
    }
    cout<<"hash_table list length statistics: "<<endl;
    for (i = 0; i < MAX_LIST_LINE; i++){
        if (a[i] > 0)
            cout<<"there are "<<a[i]<<" lists with length "<<i<<". the data count ratio against whole data count is "<< (a[i] * i * 100.0) / m_nDataCount<<" %"<<endl;
    }
    cout<<"there are "<<nExtendListNum<<" lists with exceeding length "<<MAX_LIST_LINE<<endl;
}

void printContainerElapseTime(string pszContainerName, string pszOperator, long elapse_time) {
    cout<<pszContainerName<<" test action "<<pszOperator<<" takes "<<elapse_time<<"ms"<<endl;
}

void test_hash_table() {
    cout<<"hash_table performance test:"<<endl;
    // MAX_N个数据 MAX_QUERY次查询
    const int MAX_N = 500000, MAX_QUERY = 5000000;

    int *a = new int[MAX_N];
    int *query = new int[MAX_QUERY];

    cout<<"data volume: "<<MAX_N<<"  query count: "<<MAX_QUERY<<endl;
    const int MAX_NUM = MAX_N * 4;
    const int MAX_QUERY_NUM = MAX_N * 4;
    cout<<"data range in container [0, "<<MAX_NUM<<") query data range [0, "<<MAX_QUERY_NUM<<")"<<endl;

    //随机生成在[0, MAX_NUM)范围内的MAX_N个数
    int i;
    srand((unsigned int)time(NULL));
    for (i = 0; i < MAX_N; ++i)
        a[i] = (rand() * rand()) % MAX_NUM;
    //随机生成在[0, MAX_QUERY_NUM)范围内的MAX_QUERY个数
    srand((unsigned int)time(NULL));
    for (i = 0; i < MAX_QUERY; ++i)
        query[i] = (rand() * rand()) % MAX_QUERY_NUM;

    hash_table<int>   myHashTable(6291469);
    clock_t  clockBegin, clockEnd;

    //insert
    cout<<"-----insert data-----------\n";
    clockBegin = clock();
    for (i = 0; i < MAX_N; i++)
        myHashTable.insert(a[i]);
    clockEnd = clock();
    cout<<"hash_table data entry count :"<<myHashTable.size()<<endl;
    printContainerElapseTime("Hash_table", "insert", clockEnd - clockBegin);

    //find
    cout<<"----- query data-----------\n";
    int nFindSucceedCount, nFindFailedCount;
    nFindSucceedCount = nFindFailedCount = 0;
    clockBegin = clock();
    for (i = 0; i < MAX_QUERY; ++i)
        if (myHashTable.find(query[i]))
            ++nFindSucceedCount;
        else
            ++nFindFailedCount;
    clockEnd = clock();
    printContainerElapseTime("hash_table", "find", clockEnd - clockBegin);
    cout<<"query success count: "<<nFindSucceedCount<<"    query fail count: "<<nFindFailedCount<<"\n";

    myHashTable.StatisticHashTable();
    cout<<"hash_table performance test end"<<endl;
}

#endif
