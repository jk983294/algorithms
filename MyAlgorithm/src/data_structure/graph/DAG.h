#ifndef DAG_H
#define DAG_H

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

/**
 * DAG单源最短路径算法   邻接矩阵表示
 * topologicalSort：
 * 用修改的DFS来生成拓扑顺序,能够判断是否能生成拓扑序，也就是检查环， O(V+E)
 */

static const int POSITIVE_LARGE_INT = 10000000;
static const int NEGATIVE_LARGE_INT = -10000000;

int Large_Add(int x, int y) {
    if (x == POSITIVE_LARGE_INT || y == POSITIVE_LARGE_INT)
        return POSITIVE_LARGE_INT;
    else if (x == NEGATIVE_LARGE_INT || y == NEGATIVE_LARGE_INT)
        return NEGATIVE_LARGE_INT;
    else
        return x + y;
}

class DagNode {  //邻接表节点
public:
    DagNode() {}
    DagNode(int id, int weight) {
        this->id = id;
        this->weight = weight;
        next = nullptr;
    }

public:
    int id{0};
    int weight{0};
    DagNode* next{nullptr};
};

class DAG {
public:
    DAG(int n) {
        this->n = n;

        headNodes = new DagNode[n];
        for (int i = 0; i < n; i++) {
            headNodes[i].id = i;
            headNodes[i].weight = 0;
            headNodes[i].next = nullptr;
        }

        dist = new int[n];
        path = new int[n];
        f = new int[n];
        d = new int[n];
        color = new int[n];
    }

    ~DAG() {
        delete[] dist;
        delete[] path;
        delete[] color;
        delete[] f;
        delete[] d;

        DagNode* tmp = nullptr;
        DagNode* tmp1 = nullptr;
        for (int i = 0; i < n; i++) {
            tmp = headNodes[i].next;
            tmp1 = headNodes[i].next;
            while (tmp != nullptr) {  //根据头结点释放邻接表
                tmp1 = tmp->next;
                delete tmp;
                tmp = tmp1;
            }
        }
        delete[] headNodes;
    }

    int length(int v, int w) {
        DagNode* tmp = nullptr;
        tmp = headNodes[v].next;
        while (tmp != nullptr) {  //根据头结点释放邻接表
            if (tmp->id == w)     // found
            {
                return tmp->weight;
            }
            tmp = tmp->next;
        }
        return POSITIVE_LARGE_INT;
    }

    bool topologicalSort() {  //拓扑排序,成功返回true,拓扑序放在topoSortResult中
        time = 0;
        topoSortResult.resize(0);
        for (int i = 0; i < n; i++) color[i] = 0;  //初始化为白色
        for (int i = 0; i < n; i++)
            if (color[i] == 0)
                if (!DFS_Visit(i)) return false;  //找到反向边

        reverse(topoSortResult.begin(), topoSortResult.end());
        return true;
    }

    bool DFS_Visit(int u) {  // false:找到反向边，即该图不是DAG,不存在拓扑序
        color[u] = 1;        //第一次访问到，变灰
        d[u] = time++;       //变灰时间
        DagNode* tmp = headNodes[u].next;
        while (tmp != nullptr) {
            if (color[tmp->id] == 0) {
                if (!DFS_Visit(tmp->id)) return false;
            } else if (color[tmp->id] == 1)  //灰色节点访问到灰色节点，说明存在反边
                return false;
            tmp = tmp->next;
        }
        color[u] = 2;   //后面的孩子都访问完变黑
        f[u] = time++;  //变黑时间
        topoSortResult.push_back(u);
        return true;
    }

    //返回false 说明有负回路
    bool shortestPath(int start) {  // start node
        if (topologicalSort()) {
        } else {
            // cout << " not a DAG !!!" << endl;
            return false;
        }

        root = start;
        DagNode* tmp = nullptr;
        int u, v;

        for (int i = 0; i < n; i++)  // from 1->n
        {
            dist[i] = POSITIVE_LARGE_INT;
            path[i] = -1;
        }
        dist[root] = 0;
        //按拓扑序对每边进行一次松弛
        for (vector<int>::iterator itr = topoSortResult.begin(); itr < topoSortResult.end(); itr++) {
            u = *itr;
            tmp = headNodes[u].next;
            while (tmp != nullptr) {
                v = tmp->id;
                if (Large_Add(dist[u], tmp->weight) < dist[v])  // Relax
                {
                    dist[v] = Large_Add(dist[u], tmp->weight);
                    path[v] = u;
                }
                tmp = tmp->next;
            }
        }
        return true;
    }

    void print() {
        cout << "topological order : ";
        for (vector<int>::iterator itr = topoSortResult.begin(); itr < topoSortResult.end(); itr++) cout << *itr << " ";
        cout << endl << "id_dist_father : ";
        for (int u = 0; u < n; u++) {
            cout << u << "_" << dist[u] << "_" << path[u] << " ";
        }
        cout << endl;
    }

    void trajectory(int w) {  // path from v -> w could form a triangle
        int newNode = w;
        int oldNode = w;
        while (newNode != root) {
            oldNode = newNode;
            newNode = path[newNode];
            cout << oldNode << " -> " << newNode << " ";
        }
        cout << endl;
    }

    void setEdge(int v, int w, int len) {         //有向图
        DagNode* newNode1 = new DagNode(w, len);  //插入到邻接表的第一个位置
        newNode1->next = headNodes[v].next;
        headNodes[v].next = newNode1;
    }

public:
    DagNode* headNodes;  //头结点数组  link table
    int* color;  //节点的颜色，0：白色，未访问，1：灰色，第一次访问，2：黑色，它的孩子全部被访问完
    int time;    // search time
    int *d, *f;  // d[i]第一次变灰时间  f[i] 节点变黑时间
    int* dist;   // dist[v] is least length between root and v
    int* path;   // last node to node w is path[w]
    int n;       //顶点数   n nodes from [0...n-1]
    vector<int> topoSortResult;
    int root;
};

void DAG_test() {}

#endif
