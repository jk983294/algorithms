#ifndef SPARSE_GRAPH_H
#define SPARSE_GRAPH_H

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>

#include "data_structure/heap/FibonacciHeap.h"

using namespace std;

/**
 * 稀疏图  邻接表
 * 单源最短路径算法   Dijkstra 斐波那契堆实现  O(NlgN + E)
 * 单源最短路径算法   bellmanford处理负环路 O(VE)
 * 单源最短路径算法   SPFA 处理负环路 O(kE) k=2
 * 图的遍历算法  如果该图的边较少，则用此方法比邻接矩阵O(n^2)快
 */

static const int POSITIVE_LARGE_INT = 10000000;
static const int NEGATIVE_LARGE_INT = -10000000;

class SGNode {  //邻接表节点
public:
    int id, weight;
    SGNode* next;

public:
    SGNode() {
        id = 0;
        weight = 0;
        next = nullptr;
    };
    SGNode(int id, int weight) {
        this->id = id;
        this->weight = weight;
        next = nullptr;
    };
};

class SparseGraph {
public:
    SGNode* headNodes;  //头结点数组  link table
    int* dist;          // dist[v] is least length between root and v
    int* path;          // last node to node w is path[w]
    int n;              //顶点数
    vector<bool> visited;
    vector<int> traverseResult;

public:
    SparseGraph(int n);
    ~SparseGraph();
    int length(int v, int w);             // 返回length[v][w]
    void setEdge(int v, int w, int len);  // 无向图

    //单源最短路径
    void Dijkstra(int root);                  // v is start node      无负边,更无负回路
    bool BellmanFord(int root);               // 返回false 说明有负回路
    bool SPFA(int root);                      // 返回false 说明有负回路
    vector<int> trajectory(int root, int w);  // path from root -> w could form a triangle
    //所有点对之间的最短路径 调|V|次单源最短路径

    //图遍历算法
    void visitNode(int current) {
        // cout << current << ", ";
        traverseResult.push_back(current);
    }
    void BFS(int start);                // 广度搜索，非递归，队列实现，从start点开始
    void DFS_non_recursive(int start);  // 深度搜索，非递归，栈实现，从start点开始
    void DFS_recursive(int start);      // 深度搜索，递归实现，从start点开始
private:
    void DFS_recursive_impl(int v);
    int Large_Add(int x, int y);
};
bool SparseGraph::SPFA(int start) {  // start node
    vector<int> enqueueCnt(n, 0);    // 记录节点i入队次数，超过n次即松弛超过n次有负环路
    SGNode* tmp = nullptr;
    int u, v;
    queue<int> q;
    for (int i = 0; i < n; i++) {
        dist[i] = POSITIVE_LARGE_INT;
        path[i] = -1;
    }
    dist[start] = 0;
    enqueueCnt[start]++;
    q.push(start);
    while (!q.empty()) {
        u = q.front();
        q.pop();
        tmp = headNodes[u].next;
        while (tmp != nullptr) {
            v = tmp->id;
            if (Large_Add(dist[u], tmp->weight) < dist[v]) {  // Relax
                dist[v] = Large_Add(dist[u], tmp->weight);
                path[v] = u;
                enqueueCnt[v]++;
                if (enqueueCnt[v] > n) {
                    return false;
                }  // 含有负权环
                else {
                    q.push(v);
                }
            }
            tmp = tmp->next;
        }
    }
    return true;
}
bool SparseGraph::BellmanFord(int start) {  // start node
    SGNode* tmp = nullptr;
    int u, v;
    for (int i = 0; i < n; i++) {
        dist[i] = POSITIVE_LARGE_INT;
        path[i] = -1;
    }  // init
    dist[start] = 0;

    for (int j = 0; j < n - 1; j++) {  // n-1次松弛
        for (u = 0; u < n; u++) {      // 遍历每条边
            tmp = headNodes[u].next;
            while (tmp != nullptr) {
                v = tmp->id;
                if (Large_Add(dist[u], tmp->weight) < dist[v]) {  // Relax
                    dist[v] = Large_Add(dist[u], tmp->weight);
                    path[v] = u;
                }
                tmp = tmp->next;
            }
        }
    }
    // 最后一遍松弛，还能松弛说明有负回路
    for (u = 0; u < n; u++) {
        tmp = headNodes[u].next;
        while (tmp != nullptr) {
            v = tmp->id;
            if (Large_Add(dist[u], tmp->weight) < dist[v]) {
                return false;
            }
            tmp = tmp->next;
        }
    }
    return true;
}
void SparseGraph::DFS_recursive_impl(int v) {
    // to do something at first visit v
    visitNode(v);
    visited[v] = true;
    SGNode* nextNode = nullptr;
    nextNode = headNodes[v].next;
    while (nextNode != nullptr) {  // every node w adjacent to v could launch a DFS
        if (!visited[nextNode->id]) {
            DFS_recursive_impl(nextNode->id);
        }
        nextNode = nextNode->next;
    }
}
void SparseGraph::DFS_recursive(int start) {  // 深度搜索，递归实现，从start点开始
    traverseResult.clear();
    for (int i = 0; i < n; i++) visited[i] = false;  // 初始化
    DFS_recursive_impl(start);
}
void SparseGraph::DFS_non_recursive(int start) {  // 深度搜索，非递归，栈实现，从start点开始
    traverseResult.clear();
    for (int i = 0; i < n; i++) visited[i] = false;  // 初始化
    SGNode* nextNode = nullptr;
    stack<int> st;
    st.push(start);
    int currentNode;
    while (!st.empty()) {  // stack empty means no node left
        currentNode = st.top();
        st.pop();
        // to do something at first visit v
        if (!visited[currentNode])  // may push some node already visited, so check
        {
            visitNode(currentNode);
            visited[currentNode] = true;
        }
        // add every node w adjacent to v into stack
        nextNode = headNodes[currentNode].next;
        while (nextNode != nullptr) {
            if (!visited[nextNode->id]) {
                st.push(nextNode->id);
            }
            nextNode = nextNode->next;
        }
    }
}
void SparseGraph::BFS(int start) {  // 广度搜索，非递归，队列实现，从start点开始
    traverseResult.clear();
    for (int i = 0; i < n; i++) visited[i] = false;  // 初始化
    int current = start;
    SGNode* nextNode = nullptr;
    visitNode(current);
    visited[current] = true;
    queue<int> q;
    q.push(current);
    while (!q.empty()) {
        current = q.front();
        q.pop();
        // add every node w adjacent to v into stack
        nextNode = headNodes[current].next;
        while (nextNode != nullptr) {
            if (!visited[nextNode->id]) {
                visitNode(nextNode->id);
                visited[nextNode->id] = true;
                q.push(nextNode->id);
            }
            nextNode = nextNode->next;
        }
    }
}
vector<int> SparseGraph::trajectory(int root, int w) {  // path from root -> w could form a triangle
    vector<int> route;
    int newNode = w;
    int oldNode = w;
    route.push_back(oldNode);
    while (newNode != root) {
        oldNode = newNode;
        newNode = path[newNode];
        route.push_back(newNode);
        // cout << oldNode << " -> " << newNode << endl;
    }
    reverse(route.begin(), route.end());
    return route;
}
void SparseGraph::Dijkstra(int v) {                 // v is start node
    FibonacciHeap<int, int> q;                      // 优先队列
    vector<FibonacciHeapNode<int, int>*> nodes(n);  // <length node id > tricky nodes[i]为节点i在heap中的指针
    SGNode* tmp = nullptr;
    int min, w;
    for (int i = 0; i < n; i++) {
        dist[i] = POSITIVE_LARGE_INT;
        path[i] = -1;
        if (i == v) {
            dist[i] = 0;
        }
        nodes[i] = q.insert(dist[i], i);
    }
    while (!q.empty()) {
        min = q.minimum()->data();
        q.removeMinimum();
        nodes[min] = nullptr;
        // 开始更新和u相连的边 relax
        tmp = headNodes[min].next;
        while (tmp != nullptr) {
            w = tmp->id;
            if (nodes[w] != nullptr)  // 未被选中加入S
            {
                if (dist[min] + tmp->weight < dist[w])  // relax
                {
                    q.decreaseKey(nodes[w], dist[min] + tmp->weight);
                    dist[w] = dist[min] + tmp->weight;
                    path[w] = min;
                }
            }
            tmp = tmp->next;
        }
    }
}
int SparseGraph::length(int v, int w) {
    if (v == w) return 0;
    SGNode* tmp = nullptr;
    tmp = headNodes[v].next;
    while (tmp != nullptr) {  // 根据头结点释放邻接表
        if (tmp->id == w)     // found
        {
            return tmp->weight;
        }
        tmp = tmp->next;
    }
    return POSITIVE_LARGE_INT;
}
void SparseGraph::setEdge(int v, int w, int len) {
    SGNode* newNode1 = new SGNode(w, len);  //插入到邻接表的第一个位置
    newNode1->next = headNodes[v].next;
    headNodes[v].next = newNode1;

    //    SGNode* newNode2 = new SGNode(v,len);    // 插入到邻接表的第一个位置
    //    newNode2->next = headNodes[w].next;
    //    headNodes[w].next = newNode2;
}
int SparseGraph::Large_Add(int x, int y) {
    if (x == POSITIVE_LARGE_INT || y == POSITIVE_LARGE_INT)
        return POSITIVE_LARGE_INT;
    else if (x == NEGATIVE_LARGE_INT || y == NEGATIVE_LARGE_INT)
        return NEGATIVE_LARGE_INT;
    else
        return x + y;
}
SparseGraph::SparseGraph(int n) {
    this->n = n;
    headNodes = new SGNode[n];
    for (int i = 0; i < n; i++) {
        headNodes[i].id = i;
        headNodes[i].weight = 0;
        headNodes[i].next = nullptr;
    }
    dist = new int[n];
    path = new int[n];
    visited.resize(n, false);
}
SparseGraph::~SparseGraph() {
    delete[] dist;
    delete[] path;
    SGNode *tmp = nullptr, *tmp1 = nullptr;
    for (int i = 0; i < n; i++) {
        tmp = tmp1 = headNodes[i].next;
        while (tmp != nullptr) {  // 根据头结点释放邻接表
            tmp1 = tmp->next;
            delete tmp;
            tmp = tmp1;
        }
    }
    delete[] headNodes;
}

#endif
