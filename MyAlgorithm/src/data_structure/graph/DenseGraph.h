#ifndef DENSEGRAPH_H
#define DENSEGRAPH_H

#include <memory.h>
#include <algorithm>
#include <iostream>
#include <vector>

#include "data_structure/heap/FibonacciHeap.h"

using namespace std;

/**
 * 稀疏图  邻接矩阵
 * 所有点对间最短路径   FloydWarshall  O(n^3), 稠密图，效率要高于执行|V|次Dijkstra算法
 * 单源最短路径算法   Dijkstra 斐波那契堆实现  O(NlgN + N^2)
 * 单源最短路径算法   bellmanford处理负环路 O(VE)
 * 单源最短路径算法   SPFA 处理负环路 O(kE) k=2
 * 图的遍历算法  如果该图的边较少，则用此方法比邻接矩阵O(n^2)快
 */

static const int POSITIVE_LARGE_INT = 10000000;
static const int NEGATIVE_LARGE_INT = -10000000;

class DenseGraph {
public:
    int **length;             // weight matrix
    int **dist;               // dist[u][v] is least length between u and v
    int **path;               // previous node to node w is path[w]
    int n;                    //顶点数
    int m;                    //边数
    int **residual_capacity;  //剩余容量，用来计算最大流
public:
    DenseGraph(int n);
    ~DenseGraph();
    void print();
    void setEdge(int i, int j, int len);  //有向图

    //计算所有点对之间的最短距离
    void FloydWarshall();
    vector<int> trajectory(int v, int w);  // path from v -> w could form a triangle

    //单源最短路径算法   Dijkstra
    void Dijkstra(int start);  // start is start node

    //最大流  Edmonds-Karp算法
    int Edmonds_Karp(int s, int t);  //输入源点和汇点
private:
    int Large_Add(int x, int y);
};

int DenseGraph::Edmonds_Karp(int s, int t) {
    // residual_capacity 每次计算完都会变化，所以新的一次计算需要重新初始化
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (length[i][j] < POSITIVE_LARGE_INT)
                residual_capacity[i][j] = length[i][j];
            else
                residual_capacity[i][j] = -1;
        }

    int p, q, queue[n], u, v, pre[n], flow = 0, aug;
    while (true) {
        memset(pre, -1, sizeof(pre));  //记录父节点
        for (queue[p = q = 0] = s; p <= q; p++) {  //广度优先搜索 源节点s先入队,p指向队中第一个元素，q指向队第一个空位
            u = queue[p];  //出队
            for (v = 0; v < n && pre[t] < 0; v++)
                if (residual_capacity[u][v] > 0 && pre[v] < 0) {  //当前节点与u相连，并且还没有被访问
                    pre[v] = u, queue[++q] = v;                   //入队
                }
            if (pre[t] >= 0) {
                break;
            }  //遍历到目标节点结束
        }
        if (pre[t] < 0) break;                             //不存在增广路
        aug = 0x7fff;                                      //记录最小残留容量
        for (u = pre[v = t]; v != s; v = u, u = pre[u]) {  //沿着前向记录，遍历最短增广路径获得最小残留容量
            if (residual_capacity[u][v] < aug) aug = residual_capacity[u][v];
        }
        for (u = pre[v = t]; v != s; v = u, u = pre[u]) {  //最短增广路径根据最小残留容量进行修改流量
            residual_capacity[u][v] -= aug;
            residual_capacity[v][u] += aug;
        }
        flow += aug;
    }
    return flow;
}
void DenseGraph::Dijkstra(int v) {                   // v is start node
    FibonacciHeap<int, int> q;                       //优先队列
    vector<FibonacciHeapNode<int, int> *> nodes(n);  //<length node id > tricky nodes[i]为节点i在heap中的指针
    int min;
    for (int i = 0; i < n; i++) {
        dist[v][i] = POSITIVE_LARGE_INT;
        path[v][i] = -1;
        if (i == v) {
            dist[v][i] = 0;
        }
        nodes[i] = q.insert(dist[v][i], i);
    }
    while (!q.empty()) {
        min = q.minimum()->data();
        q.removeMinimum();
        nodes[min] = nullptr;
        //开始更新和min相连的边 relax
        for (int w = 0; w < n; w++) {
            if ((nodes[w] != nullptr) && (length[min][w] < POSITIVE_LARGE_INT))  //未被选中加入S, 并且与min相连
                if (Large_Add(dist[v][min], length[min][w]) < dist[v][w]) {      // relax
                    dist[v][w] = dist[v][min] + length[min][w];
                    q.decreaseKey(nodes[w], dist[v][w]);
                    path[v][w] = min;
                }
        }
    }
}
void DenseGraph::FloydWarshall() {  //计算所有点对之间的最短距离
    // initialize A^-1
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = length[i][j];
            if (dist[i][j] < POSITIVE_LARGE_INT)
                path[i][j] = i;
            else
                path[i][j] = -1;
        }
    }
    // calculate distance
    for (int k = 0; k < n; k++) {  //依次计算A^k,最短路径只经过(0......k)节点
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (Large_Add(dist[i][k], dist[k][j]) < dist[i][j]) {  // relax
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }
}
vector<int> DenseGraph::trajectory(int v, int w) {  // path from v -> w could form a triangle
    vector<int> route;
    int newNode = w;
    int oldNode = w;
    route.push_back(oldNode);
    // cout << "trajectory from " << v << " to " << w << " : " << dist[v][w] << endl;
    while (newNode != v) {
        oldNode = newNode;
        newNode = path[v][newNode];
        route.push_back(newNode);
        // cout << oldNode << " <- " << newNode << " : " << length[newNode][oldNode] << endl;
    }
    reverse(route.begin(), route.end());
    return route;
}
DenseGraph::~DenseGraph() {
    for (int i = 0; i < n; i++) {
        delete[] length[i];
        delete[] residual_capacity[i];
        delete[] dist[i];
        delete[] path[i];
    }
    delete[] length;
    delete[] residual_capacity;
    delete[] dist;
    delete[] path;
}
DenseGraph::DenseGraph(int n) {
    this->n = n;
    length = new int *[n];
    residual_capacity = new int *[n];
    dist = new int *[n];
    path = new int *[n];
    for (int i = 0; i < n; i++) {
        length[i] = new int[n];
        residual_capacity[i] = new int[n];
        dist[i] = new int[n];
        path[i] = new int[n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            length[i][j] = POSITIVE_LARGE_INT;
            residual_capacity[i][j] = -1;  //最大流没负边
        }
    }
}
void DenseGraph::print() {
    cout << "graph : " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << length[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << "length_father : " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << dist[i][j] << "_" << path[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
void DenseGraph::setEdge(int i, int j, int len) {  //有向图
    residual_capacity[i][j] = length[i][j] = len;
    m++;
    //        length[j][i] = len;
}
int DenseGraph::Large_Add(int x, int y) {
    if (x == POSITIVE_LARGE_INT || y == POSITIVE_LARGE_INT)
        return POSITIVE_LARGE_INT;
    else if (x == NEGATIVE_LARGE_INT || y == NEGATIVE_LARGE_INT)
        return NEGATIVE_LARGE_INT;
    else
        return x + y;
}

#endif
