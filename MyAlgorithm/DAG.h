#ifndef DAG_H
#define DAG_H

#include <map>
#include <queue>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

/***********************************************************************
 DAG单源最短路径算法   邻接矩阵表示
topologicalSort ：
用修改的DFS来生成拓扑顺序,能够判断是否能生成拓扑序，也就是检查环， O(V+E)
**********************************************************************/

const int POSTIVE_LARGEINT  = 10000000;
const int NEGATIVE_LARGEINT  = -10000000;
int Large_Add(int x,int y){
    if(x == POSTIVE_LARGEINT || y== POSTIVE_LARGEINT)   return POSTIVE_LARGEINT;
    else if(x == NEGATIVE_LARGEINT || y== NEGATIVE_LARGEINT)   return NEGATIVE_LARGEINT;
    else return x+y;
}

class node{    //邻接表节点
public:
    node(){id=0;weight = 0;next = NULL;};
    node(int id,int weight){
        this->id = id;
        this->weight = weight;
        next = NULL;
    };

    int id;
    int weight;
    node* next;
};

class DAG
{
public:
    DAG(int n){
        this->n = n;

        headNodes = new node[n];
        for (int i =0;i<n;i++)
        {
            headNodes[i].id = i;
            headNodes[i].weight = 0;
            headNodes[i].next = NULL;
        }

        dist = new int[n];
        path = new int[n];
        f = new int[n];
        d= new int[n];
        color = new int[n];
    };

    ~DAG(){
        delete []dist;
        delete []path;
        delete []color;
        delete []f;
        delete []d;

        node* tmp = NULL;
        node* tmp1 = NULL;
        for (int i =0;i<n;i++)
        {
            tmp = headNodes[i].next;
            tmp1 = headNodes[i].next;
            while(tmp !=  NULL){        //根据头结点释放邻接表
                tmp1 = tmp->next;
                delete tmp;
                tmp = tmp1;
            }
        }
        delete []headNodes;
    };

    int length(int v,int w){
        node* tmp = NULL;
        tmp = headNodes[v].next;
        while(tmp !=  NULL){        //根据头结点释放邻接表
            if (tmp->id == w)    //found
            {
                return tmp->weight;
            }
            tmp = tmp->next;
        }
        return POSTIVE_LARGEINT;
    };

    bool topologicalSort(){ //拓扑排序,成功返回true,拓扑序放在topoSortResult中
        time = 0;
        topoSortResult.resize(0);
        for(int i = 0; i< n;i++)    color[i] = 0;   //初始化为白色
        for(int i = 0; i< n;i++)
            if(color[i] == 0)
                if(!DFS_Visit(i)) return false; //找到反向边

        reverse(topoSortResult.begin(), topoSortResult.end());
        return true;
    }

    bool DFS_Visit(int u){  //false:找到反向边，即该图不是DAG,不存在拓扑序
        color[u] = 1;       //第一次访问到，变灰
        d[u] = time++;  //变灰时间
        node* tmp = headNodes[u].next;
        while(tmp != NULL){
            if(color[tmp->id] == 0){
                if(!DFS_Visit(tmp->id)) return false;
            }
            else if(color[tmp->id] == 1)    //灰色节点访问到灰色节点，说明存在反边
                return false;
            tmp = tmp->next;
        }
        color[u] = 2;           //后面的孩子都访问完变黑
        f[u] = time++;  //变黑时间
        topoSortResult.push_back(u);
        return true;
    }

    //返回false 说明有负回路
    bool shortestPath(int start){    // start node
        if(topologicalSort()){
        }
        else{   cout<<" not a DAG !!!"<<endl;   return false;}

        root = start;
        node* tmp = NULL;
        int u,v;

        for (int i = 0; i < n; i++)    //from 1->n
        {
            dist[i] = POSTIVE_LARGEINT;
            path[i] = -1;
        }
        dist[root] = 0;
        //按拓扑序对每边进行一次松弛
        for(vector<int>::iterator itr = topoSortResult.begin(); itr < topoSortResult.end(); itr++){
            u = *itr;
            tmp = headNodes[u].next;
            while(tmp != NULL){
                v = tmp->id;
                if (Large_Add(dist[u],tmp->weight) < dist[v])   //Relax
                {
                    dist[v] = Large_Add(dist[u],tmp->weight);
                    path[v] = u;
                }
                tmp = tmp->next;
            }
        }
        return true;
    };

    void print(){
        cout<<"topological order : ";
        for(vector<int>::iterator itr = topoSortResult.begin(); itr < topoSortResult.end(); itr++)
            cout<<*itr<<" ";
        cout<<endl<<"id_dist_father : ";
        for(int u = 0; u < n; u++){ cout<<u<<"_"<<dist[u]<<"_"<<path[u]<<" ";}
        cout<<endl;
    };


    void trijactory(int w){//path from v -> w could form a triangle
        int newnode = w;
        int oldnode = w;
        while(newnode != root){
            oldnode = newnode;
            newnode = path[newnode];
            cout<<oldnode<<" -> "<<newnode<<" ";
        }
        cout<<endl;
    };

    void setEdge(int v,int w,int len){    //有向图
        node* newnode1 = new node(w,len);    //插入到邻接表的第一个位置
        newnode1->next = headNodes[v].next;
        headNodes[v].next = newnode1;

//      node* newnode2 = new node(v,len);    //插入到邻接表的第一个位置
//      newnode2->next = headNodes[w].next;
//      headNodes[w].next = newnode2;
    };

    node* headNodes;        //头结点数组  link table
    int *color;    //节点的颜色，0：白色，未访问，1：灰色，第一次访问，2：黑色，它的孩子全部被访问完
    int time;   //search time
    int *d,*f;  //d[i]第一次变灰时间  f[i] 节点变黑时间
    int *dist;                        //dist[v] is least length between root and v
    int *path;    //last node to node w is path[w]
    int n;            //顶点数   n nodes from [0...n-1]
    vector<int> topoSortResult;
    int root;
};



void DAG_test(){
    DAG g(6);    //5 nodes
    //例子来自算法导论 365
    g.setEdge(0,1,5);
    g.setEdge(0,2,3);
    g.setEdge(1,2,2);
    g.setEdge(1,3,6);
    g.setEdge(2,3,7);
    g.setEdge(2,4,4);
    g.setEdge(2,5,2);
    g.setEdge(3,4,-1);
    g.setEdge(3,5,1);
    g.setEdge(4,5,-2);
//    g.setEdge(5,0,1);      //加了一条回边，测试拓扑排序

    //0 is root
    if(g.shortestPath(0)){
            g.print();
    }
    if(g.shortestPath(2)){
            g.print();
    }

}

#endif
