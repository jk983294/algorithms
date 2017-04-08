#ifndef MST_PRIM_H
#define MST_PRIM_H

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>

using namespace std;
/************************************************************************/
/*  minimum-cost spanning tree
    suit for dense graph, because it maintain vertices length to current MST
    O( V * T[extract_min] + E * T[change_weight] )
    adjacent matrix        O(V^2)                 T[extract_min] is O(V) by scan nearest array      T[change_weight]is O(1) to change nearest array
    heap                  O(V*lgV + E*lgV)       T[extract_min] is O(lgV) to delete in heap        T[change_weight] is O(lgV)
    node 0 --> n-1
*/
/************************************************************************/

const int MAX_NODES = 10;                                            // max node count
const int MAX_LENGTH = 99999;                                        // max weight of an edge

class PrimNode{
public:
    PrimNode(): id(0), weight(0), next(NULL){};
    void set(int id,int weight){
        this->id = id;
        this->weight = weight;
        next = NULL;
    };
public:
    int id;
    int weight;
    PrimNode* next;
};

class MST_Prim
{
public:
    int n;                                                            //node count
    int cost[MAX_NODES][MAX_NODES];
    vector<int> nearest;
    // nearest[w] = v,表示已经选择到集合TV中的w到不在集合TV中的最短边是(w,v),如果v=-1,表示不存在这样的边
    vector<bool> selected;                                            //是否被选入TV集合
    //邻接表表示找最小轻边用二叉堆
    PrimNode* headNodes;                                            //头结点数组  link table
public:
    MST_Prim(int n);
    ~MST_Prim();
    void refresh(int v);                                            //新的节点v被选进集合TV后更新nearest
    void Prim_Array();
    void setEdge(int x,int y,int weight){                            //无向图
        cost[x][y] = weight;
        cost[y][x] = weight;
    };
};

MST_Prim::MST_Prim(int n){
    this->n = n;
    for (int i=0; i < n; i++){
        for (int j = 0; j < n; j++){
            cost[i][j] = MAX_LENGTH;
        }
    }

    headNodes = new PrimNode[n];
    for (int i = 0; i < n; i++){
        headNodes->set(i, 0);
    }
}
void MST_Prim::refresh(int v){
    for (int i =0; i< n; i++)
    {
        if ((cost[v][i] < MAX_LENGTH) && (selected[i] == false ))    //i节点与v相连，并且不在TV set中，否则出现环
        {
            if (nearest[i] < 0){
                nearest[i] = v;
            }
            else if (cost[v][i] < cost[nearest[i]][i]){
                nearest[i] = v;
            }
        }
    }
}
void MST_Prim::Prim_Array(){
    vector<pair<int, int> > edges;                                    // 记录选中的边
    nearest.resize(n, -1);
    selected.resize(n,false);
    int u, v, min_cost, min_index;
    selected[0] = true;                                                // begin from node 0
    refresh(0);
    while (edges.size() < n-1)
    {
        min_cost = MAX_LENGTH;
        min_index = -1;
        for (v =0; v < nearest.size(); v++)                            // find next best edge(u,v)
        {
            //v not belong set TV
            if (!selected[v] && (nearest[v] >= 0)  && (cost[v][nearest[v]] < min_cost))
            {
                min_cost = cost[v][nearest[v]];
                min_index = v;
            }
        }
        if (min_index < 0)                                            // don't exist this edge
        {
            break;
        } else {
            v = min_index;
            u = nearest[v];
            selected[v] = true;
            refresh(v);
            edges.push_back(make_pair(u, v));
        }
    }
    if (edges.size() < n-1) {
        cout<<"don't exist this mst"<<endl;
    } else{
        cout<<"mst is :"<<endl;
        for (int i =0; i < edges.size(); i++){
            cout << edges[i].first << " " << edges[i].second <<endl;
        }
    }
}
MST_Prim::~MST_Prim(){
    PrimNode* tmp = NULL;
    PrimNode* tmp1 = NULL;
    for (int i =0; i<n; ++i)
    {
        tmp = headNodes[i].next;
        tmp1 = headNodes[i].next;
        while(tmp !=  NULL){                                        //根据头结点释放邻接表
            tmp1 = tmp->next;
            delete tmp;
            tmp = tmp1;
        }
    }
    delete []headNodes;
}
/************************************************************************/
/* 1->2 1->3 2->3 3->4 1->4                                             */
/************************************************************************/


void graph_MST_Prim(){
    MST_Prim g(7);                                    //4 nodes
    // 10 edge  (v,w)
    g.setEdge(0, 5, 10);
    g.setEdge(0, 1, 22);
    g.setEdge(1, 2, 6);
    g.setEdge(1, 6, 2);
    g.setEdge(5, 6, 7);
    g.setEdge(5, 4, 3);
    g.setEdge(6, 2, 9);
    g.setEdge(6, 4, 11);
    g.setEdge(4, 3, 12);
    g.setEdge(2, 3, 23);

    g.Prim_Array();
    cout<<endl;
}

#endif
