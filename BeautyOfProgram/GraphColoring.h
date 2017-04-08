#ifndef GRAPHCOLORING_H
#define GRAPHCOLORING_H

#include "myutility.h"
/************************************************************************/
/* 图着色问题                                                            */
/************************************************************************/

class MyGraph{
public:
    vector<vector<int> > linktable;                 //邻接表
    int nodecount;                                  //节点数
    vector<int> colors;                             //每个节点的着色
public:
    MyGraph(int nodecount);
    void setedge(int v,int w);

//图着色问题
    void coloring();
    bool ckeck_if_same_color_adjacent();            //检测当前的着色方案colors有没有相同颜色连接着

//二部图问题
public:
    bool is_BiPartite();                            //判断一个连通无向图G是否是二部图

//支持sting型的数据转为图
public:
    set<string> allstrings;
    map<string, int> string2nodeid;
    int nextnodeid;
    void setedge(string a,string b);
};

void test_GraphColoring();
void test_is_BiPartite();


#endif
