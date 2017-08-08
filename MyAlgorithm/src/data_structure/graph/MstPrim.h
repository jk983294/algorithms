#ifndef MST_PRIM_H
#define MST_PRIM_H

#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <vector>

using namespace std;

/**
 * minimum-cost spanning tree
 * greedy algorithm, locally optimal choice is globally optimal
 * suit for dense graph, because it maintain vertices length to current MST
 * O( V * T[extract_min] + E * T[change_weight] )
 * adjacent matrix O(V^2)
 * T[extract_min] is O(V) by scan nearest array, T[change_weight] is O(1) to change nearest array
 * heap O(V*lgV + E*lgV)
 * T[extract_min] is O(lgV) to delete in heap, T[change_weight] is O(lgV)
 * node 0 --> n-1
 */

static const int MAX_NODES = 10;      // max node count
static const int MAX_LENGTH = 99999;  // max weight of an edge

class PrimNode {
public:
    PrimNode() {}
    void set(int id, int weight) {
        this->id = id;
        this->weight = weight;
        next = nullptr;
    }

public:
    int id{0};
    int weight{0};
    PrimNode* next{nullptr};
};

class MstPrim {
public:
    size_t n;  // node count
    int cost[MAX_NODES][MAX_NODES];
    vector<int> nearest;
    // nearest[w] = v,表示已经选择到集合TV中的w到不在集合TV中的最短边是(w,v),如果v=-1,表示不存在这样的边
    vector<bool> selected;  //是否被选入TV集合
    // 邻接表表示找最小轻边用二叉堆
    PrimNode* headNodes;  // 头结点数组  link table
public:
    MstPrim(int n);
    ~MstPrim();
    void refresh(int v);  // 新的节点v被选进集合TV后更新nearest
    set<pair<int, int>> prim();
    void setEdge(int x, int y, int weight) {  //无向图
        cost[x][y] = weight;
        cost[y][x] = weight;
    };
};

MstPrim::MstPrim(int n) {
    this->n = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cost[i][j] = MAX_LENGTH;
        }
    }

    headNodes = new PrimNode[n];
    for (int i = 0; i < n; i++) {
        headNodes->set(i, 0);
    }
}
void MstPrim::refresh(int v) {
    for (size_t i = 0; i < n; i++) {
        if ((cost[v][i] < MAX_LENGTH) && (selected[i] == false))  // i节点与v相连，并且不在TV set中，否则出现环
        {
            if (nearest[i] < 0) {
                nearest[i] = v;
            } else if (cost[v][i] < cost[nearest[i]][i]) {
                nearest[i] = v;
            }
        }
    }
}
set<pair<int, int>> MstPrim::prim() {
    set<pair<int, int>> edges;  // 记录选中的边
    nearest.resize(n, -1);
    selected.resize(n, false);
    size_t u, v, min_index;
    int min_cost;
    selected[0] = true;  // begin from node 0
    refresh(0);
    while (edges.size() < n - 1) {
        min_cost = MAX_LENGTH;
        min_index = -1;
        for (v = 0; v < nearest.size(); v++)  // find next best edge(u,v)
        {
            // v not belong set TV
            if (!selected[v] && (nearest[v] >= 0) && (cost[v][nearest[v]] < min_cost)) {
                min_cost = cost[v][nearest[v]];
                min_index = v;
            }
        }
        if (min_index < 0)  // don't exist this edge
        {
            break;
        } else {
            v = min_index;
            u = nearest[v];
            selected[v] = true;
            refresh(v);
            edges.insert({u, v});
        }
    }
    if (edges.size() < n - 1) {
        cerr << "don't exist this mst" << endl;
    } else {
        //        cout << "mst is :" << endl;
        //        for (auto& edge : edges) {
        //            cout << edge.first << " " << edge.second << endl;
        //        }
    }
    return edges;
}
MstPrim::~MstPrim() {
    PrimNode* tmp = nullptr;
    PrimNode* tmp1 = nullptr;
    for (size_t i = 0; i < n; ++i) {
        tmp = headNodes[i].next;
        tmp1 = headNodes[i].next;
        while (tmp != nullptr) {  // 根据头结点释放邻接表
            tmp1 = tmp->next;
            delete tmp;
            tmp = tmp1;
        }
    }
    delete[] headNodes;
}

#endif
