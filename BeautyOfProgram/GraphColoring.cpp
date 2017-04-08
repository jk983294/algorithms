#include "GraphColoring.h"


void test_is_BiPartite(){
    MyGraph gc(7);
    gc.setedge(0,3);
    gc.setedge(0,4);
    gc.setedge(0,5);
    gc.setedge(1,4);
    gc.setedge(1,6);
    gc.setedge(2,3);
    gc.setedge(2,5);
//  gc.setedge(6,5);            //加上之后不是二部图
//  gc.setedge("a","d");
//  gc.setedge("a","e");
//  gc.setedge("a","f");
//  gc.setedge("b","e");
//  gc.setedge("b","g");
//  gc.setedge("c","d");
//  gc.setedge("c","f");
//  gc.setedge("g","f");        //加上之后不是二部图
    cout<<gc.is_BiPartite()<<endl;
}
void test_GraphColoring(){
    MyGraph gc(4);
    gc.setedge(0,1);    gc.setedge(0,3); gc.setedge(0,2); gc.setedge(2,1); gc.setedge(2,3);
    gc.coloring();
}

//判断一个连通无向图G是否是二部图
bool MyGraph::is_BiPartite(){               //从顶点编号0开始广搜,是二部图返回true,否则返回false
    int head,h,t;                           //head表示队头，t是队尾
    vector<int> dis(nodecount , -1);        //每个顶点到顶点0的最短距离        初始化顶点未访问
    vector<int> q(nodecount);               //BFS使用的队列
    int i,j;
    dis[0] = 0;
    head = h = t = 0;
    while(t <= h)
    {
        for(i = t; i <= h; ++i)
            for(j = 0; j < nodecount; ++j){
                if(linktable[q[i]][j] > 0) {
                    if(j == q[i])    continue;                              //排除自环
                    if(dis[j] != -1 && (dis[q[i]] - dis[j]) % 2 == 0)       //说明顶点q[i]和顶点j连接会有奇环产生，不是二部图
                        return false;
                    else if(dis[j] == -1){                                  //j没有访问过，入队
                        q[++head] = j;
                        dis[j] = dis[q[i]] + 1;
                    }
                }
            }
        t = h + 1,h = head;
    }
    return true;
}
MyGraph::MyGraph(int nodecount){
    this->nodecount = nodecount;
    colors.resize(nodecount);
    make_two_demision_vector(nodecount,nodecount,-1,linktable);
    nextnodeid = 0;
}
void MyGraph::setedge(int v,int w){
    linktable[v][w] = 1;
    linktable[w][v] = 1;
}
void MyGraph::setedge(string a,string b){
    int n1,n2;
    if(allstrings.find(a) == allstrings.end()){
        n1 = nextnodeid++;        allstrings.insert(a);
        string2nodeid.insert(pair<string,int>(a,n1));
    }else{    n1 = string2nodeid[a];    }
    if(allstrings.find(b) == allstrings.end()){
        n2 = nextnodeid++;        allstrings.insert(b);
        string2nodeid.insert(pair<string,int>(b,n2));
    }else{    n2 = string2nodeid[b];    }
    linktable[n1][n2] = 1;    linktable[n2][n1] = 1;
}
void MyGraph::coloring(){
    int colornum = 2;
    bool found = false;
    while (1){
        fill(colors.begin(),colors.end(), 0);                           //每个节点的颜色都初始化为第一种
        do {
            cout<<colors<<endl;
            if(!ckeck_if_same_color_adjacent()){
                found = true;  break;                                   //找到
            }
        } while (generate_all_k_choices(colors,nodecount,colornum));
        if(found)    break;
        ++colornum;
    }
    cout<<"need color : "<<colornum<<endl;
    cout<<"color result : "<<colors<<endl;
}
bool MyGraph::ckeck_if_same_color_adjacent(){
    for (int i = 0; i < nodecount; ++i)    {
        for (int j = i+1; j < nodecount; ++j)    {                      //上三角
            if (linktable[i][j] > 0  && colors[i] == colors[j] ){       //节点相连并且颜色相同
                return true;
            }
        }
    }
    return false;
}
