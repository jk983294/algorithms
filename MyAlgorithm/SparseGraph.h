#ifndef SPARSEGRAPH_H
#define SPARSEGRAPH_H


#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>

#include "FibonacciHeap.h"

using namespace std;

/************************************************************************
 稀疏图  邻接表
单源最短路径算法   Dijkstra 斐波那契堆实现  O(NlgN + E)
单源最短路径算法   bellmanford处理负环路 O(VE)
单源最短路径算法   SPFA 处理负环路 O(kE) k=2
图的遍历算法  如果该图的边较少，则用此方法比邻接矩阵O(n^2)快
************************************************************************/

class GNode{    //邻接表节点
public:
    int id, weight;
    GNode* next;
public:
    GNode(){id=0;weight = 0;next = NULL;};
    GNode(int id,int weight){    this->id = id;  this->weight = weight;  next = NULL;};
};

class SparseGraph
{
public:
    GNode* headNodes;        //头结点数组  link table
    int *dist;                        //dist[v] is least length between root and v
    int *path;    //last node to node w is path[w]
    int n;            //顶点数
    vector<bool> visited;
public:
    SparseGraph(int n);
    ~SparseGraph();
    int length(int v,int w);    //返回length[v][w]
    void setEdge(int v,int w,int len);    //无向图

    //单源最短路径
    void Dijkstra(int root);    // v is start node      无负边,更无负回路
    bool BellmanFord(int root);  //返回false 说明有负回路
    bool SPFA(int root);               //返回false 说明有负回路
    void trijactory(int root,int w);    //path from root -> w could form a triangle
    //所有点对之间的最短路径 调|V|次单源最短路径


    //图遍历算法
    void visitNode(int current){    cout<<current<<" "; }
    void BFS(int start);        //广度搜索，非递归，队列实现，从start点开始
    void DFS_nonrecursive(int start);        //深度搜索，非递归，栈实现，从start点开始
    void DFS_recursive(int start);                 //深度搜索，递归实现，从start点开始
private:
    void DFS_recursive_impl(int v);
    int Large_Add(int x,int y);
    static int POSTIVE_LARGEINT;
    static int NEGATIVE_LARGEINT;
};
int SparseGraph::POSTIVE_LARGEINT  = 10000000;
int SparseGraph::NEGATIVE_LARGEINT  = -10000000;
bool SparseGraph::SPFA(int start){    // start node
    vector<int> enqueueCnt(n,0);    //记录节点i入队次数，超过n次即松弛超过n次有负环路
    GNode* tmp = NULL;
    int u,v;
    queue<int> q;
    for (int i = 0; i < n; i++){    dist[i] = POSTIVE_LARGEINT; path[i] = -1;}
    dist[start] = 0;     enqueueCnt[start]++;    q.push(start);
    while(!q.empty()){
        u = q.front();    q.pop();
        tmp = headNodes[u].next;
        while(tmp != NULL){
            v = tmp->id;
            if (Large_Add(dist[u],tmp->weight) < dist[v]){   //Relax
                dist[v] = Large_Add(dist[u],tmp->weight);
                path[v] = u;
                enqueueCnt[v]++;
                if(enqueueCnt[v] > n){  return false;}  //含有负权环
                else { q.push(v); }
            }
            tmp = tmp->next;
        }
    }
    return true;
}
bool SparseGraph::BellmanFord(int start){    // start node
    GNode* tmp = NULL;
    int u,v;
    for (int i = 0; i < n; i++){    dist[i] = POSTIVE_LARGEINT;     path[i] = -1;   }   //init
    dist[start] = 0;

    for(int j = 0; j < n-1; j++){    //n-1次松弛
        for(u = 0; u < n; u++){  //遍历每条边
            tmp = headNodes[u].next;
            while(tmp != NULL){
                v = tmp->id;
                if (Large_Add(dist[u],tmp->weight) < dist[v]){   //Relax
                    dist[v] = Large_Add(dist[u],tmp->weight);   path[v] = u;
                }
                tmp = tmp->next;
            }
        }
    }
    //最后一遍松弛，还能松弛说明有负回路
    for(u = 0; u < n; u++){
        tmp = headNodes[u].next;
        while(tmp != NULL){
            v = tmp->id;
            if (Large_Add(dist[u],tmp->weight) < dist[v]){  return false;}
            tmp = tmp->next;
        }
    }
    return true;
}
void SparseGraph::DFS_recursive_impl(int v){
    //to do something at first visit v
    visitNode(v);   visited[v] = true;
    GNode* nextnode = NULL;
    nextnode = headNodes[v].next;
    while(nextnode !=  NULL){        //every node w adjcent to v could launch a DFS
        if (! visited[nextnode->id]){   DFS_recursive_impl(nextnode->id);}
        nextnode = nextnode->next;
    }
}
void SparseGraph::DFS_recursive(int start){        //深度搜索，递归实现，从start点开始
    for (int i = 0; i< n; i++)    visited[i] = false;    //初始化
    DFS_recursive_impl(start);
}
void SparseGraph::DFS_nonrecursive(int start){        //深度搜索，非递归，栈实现，从start点开始
    for (int i = 0; i< n; i++)    visited[i] = false;    //初始化
    GNode* nextnode = NULL;
    stack<int> st;
    st.push(start);
    int currentNode;
    while(!st.empty()){        //stack empty means no node left
        currentNode = st.top();     st.pop();
        //to do something at first visit v
        if (! visited[currentNode])        //may push some node already visited, so check
        {
            visitNode(currentNode);
            visited[currentNode] = true;
        }
        //add every node w adjcent to v into stack
        nextnode = headNodes[currentNode].next;
        while(nextnode !=  NULL){
            if (! visited[nextnode->id]){   st.push(nextnode->id);  }
            nextnode = nextnode->next;
        }
    }
}
void SparseGraph::BFS(int start){        //广度搜索，非递归，队列实现，从start点开始
    for (int i = 0; i< n; i++)    visited[i] = false;    //初始化
    int current = start;
    GNode* nextnode = NULL;
    visitNode(current);     visited[current] = true;
    queue<int> q;
    q.push(current);
    while (! q.empty())
    {
        current = q.front();    q.pop();
        //add every node w adjcent to v into stack
        nextnode = headNodes[current].next;
        while(nextnode !=  NULL){
            if (! visited[nextnode->id])
            {
                visitNode(nextnode->id);    visited[nextnode->id] = true;
                q.push(nextnode->id);
            }
            nextnode = nextnode->next;
        }
    }
}
void SparseGraph::trijactory(int root,int w){//path from root -> w could form a triangle
    int newnode = w;
    int oldnode = w;
    while(newnode != root){
        oldnode = newnode;
        newnode = path[newnode];
        cout<<oldnode<<" -> "<<newnode<<endl;
    }
}
void SparseGraph::Dijkstra(int v){    // v is start node
    FibonacciHeap<int, int > q;  //优先队列
    vector <FibonacciHeapNode<int, int >*> nodes(n);   //<length nodeid > tricky nodes[i]为节点i在heap中的指针
    GNode* tmp = NULL;
    int min,w;
    for (int i = 0; i < n; i++)
    {
        dist[i] = POSTIVE_LARGEINT;     path[i] = -1;
        if ( i == v ) { dist[i] = 0; }
        nodes[i] = q.insert(dist[i],i);
    }
    while(!q.empty()){
        min = q.minimum()->data();
        q.removeMinimum();  nodes[min] = NULL;
        //开始更新和u相连的边 relax
        tmp = headNodes[min].next;
        while(tmp != NULL){
            w = tmp->id;
            if (nodes[w] != NULL)   //未被选中加入S
            {
                if (dist[min]+tmp->weight < dist[w])    //relax
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
int SparseGraph::length(int v,int w){
    if(v==w)    return 0;
    GNode* tmp = NULL;
    tmp = headNodes[v].next;
    while(tmp !=  NULL){        //根据头结点释放邻接表
        if (tmp->id == w)    //found
        {
            return tmp->weight;
        }
        tmp = tmp->next;
    }
    return POSTIVE_LARGEINT;
}
void SparseGraph::setEdge(int v,int w,int len){
    GNode* newnode1 = new GNode(w,len);    //插入到邻接表的第一个位置
    newnode1->next = headNodes[v].next;
    headNodes[v].next = newnode1;

//    GNode* newnode2 = new GNode(v,len);    //插入到邻接表的第一个位置
//    newnode2->next = headNodes[w].next;
//    headNodes[w].next = newnode2;
}
int SparseGraph::Large_Add(int x,int y){
    if(x == POSTIVE_LARGEINT || y== POSTIVE_LARGEINT)   return POSTIVE_LARGEINT;
    else if(x == NEGATIVE_LARGEINT || y== NEGATIVE_LARGEINT)   return NEGATIVE_LARGEINT;
    else return x+y;
}
SparseGraph::SparseGraph(int n){
    this->n = n;
    headNodes = new GNode[n];
    for (int i =0;i<n;i++)
    {
        headNodes[i].id = i;    headNodes[i].weight = 0;    headNodes[i].next = NULL;
    }
    dist = new int[n];
    path = new int[n];
    visited.resize(n,false);
}
SparseGraph::~SparseGraph(){
    delete []dist;
    delete []path;
    GNode *tmp = NULL,   *tmp1 = NULL;
    for (int i =0;i<n;i++)
    {
        tmp =tmp1 = headNodes[i].next;
        while(tmp !=  NULL){        //根据头结点释放邻接表
            tmp1 = tmp->next;   delete tmp;     tmp = tmp1;
        }
    }
    delete []headNodes;
}

void bellmanford_spfa_test();
void SparseGraph_test(){
    SparseGraph g(5);    //5 nodes
    // example from 算法导论 P367
    g.setEdge(0,1,10);
    g.setEdge(0,3,5);
    g.setEdge(1,2,1);
    g.setEdge(1,3,2);
    g.setEdge(2,4,4);
    g.setEdge(3,1,3);
    g.setEdge(3,2,9);
    g.setEdge(3,4,2);
    g.setEdge(4,0,7);
    g.setEdge(4,2,6);

    cout<<"Dijkstra test begin:"<<endl;
    int root = 0, target = 2;
    g.Dijkstra(root);
    g.trijactory(root,target);        //route from root to target
    cout<<"Dijkstra test end."<<endl;

    cout<<endl<<"traverse test begin:"<<endl;
    g.DFS_nonrecursive(0);  cout<<endl;
    g.DFS_recursive(0); cout<<endl;
    g.BFS(0);   cout<<endl;
    cout<<"traverse test end:"<<endl;

    bellmanford_spfa_test();
}
void bellmanford_spfa_test(){
    SparseGraph g(5);    //5 nodes
    //例子来自算法导论 362
    g.setEdge(0,1,6);
    g.setEdge(0,3,7);
    g.setEdge(1,2,5);
    g.setEdge(1,3,8);   //g.setEdge(1,3,8); 无负环 g.setEdge(1,3,4); 有负环
    g.setEdge(1,4,-4);
    g.setEdge(2,1,-2);
    g.setEdge(3,2,-3);
    g.setEdge(3,4,9);
    g.setEdge(4,0,2);
    g.setEdge(4,2,7);

    cout<<endl<<"SPFA test : "<<endl;
    //0 is root
    if(g.SPFA(0)){
        g.trijactory(0,4);        //route from start to 4
    }
    else{   cout<<" negative loop !!!"<<endl;}
    cout<<"SPFA test end."<<endl;
    cout<<endl<<"BellmanFord test : "<<endl;
    if(g.BellmanFord(0)){
        g.trijactory(0,4);        //route from start to 4
    }
    else{   cout<<" negative loop !!!"<<endl;}
    cout<<"BellmanFord test end."<<endl;
}

#endif
