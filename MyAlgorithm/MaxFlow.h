#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

#define VMAX 201
int n, m;        //分别表示图的边数和顶点数
int c[VMAX][VMAX];

int Edmonds_Karp( int s, int t ){    //输入源点和汇点
    int p, q, queue[VMAX], u, v, pre[VMAX], flow= 0, aug;
    while(true){
        memset(pre,-1,sizeof(pre));        //记录父节点
        for( queue[p=q=0]=s; p<=q; p++ ){    //广度优先搜索
            u= queue[p];
            for( v=0; v<m&&pre[t]<0; v++ )
                if( c[u][v]>0 && pre[v]<0 )
                    pre[v]=u, queue[++q]=v;
            if( pre[t]>=0 )    break;
        }
        if( pre[t]<0 )    break;        //不存在增广路
        aug= 0x7fff;    //记录最小残留容量
        for( u=pre[v=t]; v!=s; v=u,u=pre[u] )
            if(c[u][v]<aug)    aug=c[u][v];
        for( u=pre[v=t]; v!=s; v=u,u=pre[u] )
            c[u][v]-=aug, c[v][u]+=aug;
        flow+= aug;
    }
    return flow;
}
void init_matrix(){
    for (int i =0; i<m;i++)
    {
        for (int j = 0; j<m;j++)
        {
            c[i][j] = -1;
        }
    }
}
int main(){
    int T=0, N = 0, M = 0;
    cin>>T;
    vector<bool> results(0);
    vector<int> caseNum(T);
    bool result;
    int a,b,len,content = 0,previous_content=0;

    for (int i =0; i< T;i++)
    {
        cin>>N>>M;        //nodes edges
        n = M; m = N;
        content = 0;
        previous_content = 0;
        init_matrix();
        for (int j =0; j< M;j++)
        {
            cin>>a>>b>>len;
            c[a-1][b-1] = len;
            content = Edmonds_Karp(0,N-1);
            if (content-previous_content > 0)
            {
                cout<<j+1<<" "<<content-previous_content<<endl;
                previous_content = content;
            }
        }
    }

    return 0;
}
