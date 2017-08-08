#ifndef MST_KRUSKAL_H
#define MST_KRUSKAL_H

#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <vector>

using namespace std;

/**
 * 图的最小生成树(minimum-cost spanning tree)
 * greedy algorithm, locally optimal choice is globally optimal
 * Kruskal 采用并查集来判断是否形成环 O(e * loge)  适用于稀疏图
 * 节点从 0 --> n-1
 */
class KruskalEdge {
public:
    KruskalEdge() {}
    KruskalEdge(int x, int y, int weight) {
        this->x = x;
        this->y = y;
        this->weight = weight;
    }

    int x{0};
    int y{0};
    int weight{0};
};
bool operator>(const KruskalEdge &t1, const KruskalEdge &t2) {
    return t1.weight > t2.weight;  //按weight从小到大出队
}

class KruskalGraph {
public:
    KruskalGraph(int n) { this->n = n; };
    ~KruskalGraph(){};
    // Union Find Set
    // find element i's root, make node in path(i->root) directly point to root
    int uf_collapse_find(int i) {
        int r = i;
        for (r = i; parent[r] >= 0; r = parent[r])
            ;  // find root
        while (i != r) {
            int s = parent[i];
            parent[i] = r;  // directly point to root
            i = s;
        }
        return r;
    }

    // 集合i合并到集合j中，i,j是集合的根,|parent[i]|为集合i的元素个数,尽量让树高变低
    void uf_weight_union(int i, int j) {
        int tmp = parent[i] + parent[j];  // tmp = - (|parent[i]| + |parent[j]|)
        if (parent[j] < parent[i])        // tree i's nodes is less
        {
            parent[i] = j;
            parent[j] = tmp;
        } else {  // tree j's nodes is less
            parent[j] = i;
            parent[i] = tmp;
        }
    }

    vector<KruskalEdge> Kruskal() {  // 每次选择一条最短边加入，如果没有环则继续
        parent.resize(n, -1);        // every node is a set
        priority_queue<KruskalEdge, vector<KruskalEdge>, greater<KruskalEdge>> q;  // 按weight从小到大出队
        for (vector<KruskalEdge>::iterator it = Edges.begin(); it < Edges.end(); it++) {
            q.push(*it);
        }

        KruskalEdge current;
        vector<KruskalEdge> selected;
        while ((selected.size() < n - 1) && (!q.empty())) {
            current = q.top();  //与正常的queue不一样，正常的用front()获得
            q.pop();
            if (!isLoop(current)) {
                selected.push_back(current);
            }
        }

        if (selected.size() < n - 1) {
            cerr << "don't exist this mst" << endl;
        }
        return selected;
    }

    bool isLoop(KruskalEdge &e) {  // 判断新加入的边是否形成环路
        int root1 = uf_collapse_find(e.x);
        int root2 = uf_collapse_find(e.y);
        if (root1 == root2)  // 两个节点都在并查集中就形成环
            return true;
        else {
            uf_weight_union(root1, root2);  // 不形成环，则该边选中，两个集合合并
            return false;
        }
    }

    void setEdge(int x, int y, int weight) {  // 无向图
        KruskalEdge e(x, y, weight);
        Edges.push_back(e);
    }

public:
    size_t n;  // node count
    vector<KruskalEdge> Edges;
    vector<int> parent;  // 并查集
};

#endif
