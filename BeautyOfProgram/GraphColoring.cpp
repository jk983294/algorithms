#include "MyUtility.h"

class MyGraph {
public:
    vector<vector<int> > linkTable;  // 邻接表
    int nodeCount;                   // 节点数
    vector<int> colors;              // 每个节点的着色

public:
    // 支持sting型的数据转为图
    set<string> allStrings;
    map<string, int> string2nodeId;
    int nextNodeId;

public:
    MyGraph(int count);
    void set_edge(int v, int w);
    void set_edge(string a, string b);

    // 图着色问题
    void coloring();
    bool check_if_same_color_adjacent();  // 检测当前的着色方案colors有没有相同颜色连接着

public:
    bool is_bi_partite();  // 判断一个连通无向图G是否是二部图
};

void test_graph_coloring();
void test_is_bi_partite();

int main() {
    test_graph_coloring();  //着色问题  No 1.9 见面会安排
    test_is_bi_partite();   //检测一个图是不是二部图
    return 0;
}

void test_is_bi_partite() {
    MyGraph gc(7);
    gc.set_edge(0, 3);
    gc.set_edge(0, 4);
    gc.set_edge(0, 5);
    gc.set_edge(1, 4);
    gc.set_edge(1, 6);
    gc.set_edge(2, 3);
    gc.set_edge(2, 5);
    //  gc.set_edge(6,5);            //加上之后不是二部图

    //  gc.set_edge("a","d");
    //  gc.set_edge("a","e");
    //  gc.set_edge("a","f");
    //  gc.set_edge("b","e");
    //  gc.set_edge("b","g");
    //  gc.set_edge("c","d");
    //  gc.set_edge("c","f");
    //  gc.set_edge("g","f");        //加上之后不是二部图
    cout << gc.is_bi_partite() << endl;
}
void test_graph_coloring() {
    MyGraph gc(4);
    gc.set_edge(0, 1);
    gc.set_edge(0, 3);
    gc.set_edge(0, 2);
    gc.set_edge(2, 1);
    gc.set_edge(2, 3);
    gc.coloring();
}

// 判断一个连通无向图G是否是二部图
bool MyGraph::is_bi_partite() {      // 从顶点编号0开始广搜,是二部图返回true,否则返回false
    int head, h, t;                  // head表示队头，t是队尾
    vector<int> dis(nodeCount, -1);  // 每个顶点到顶点0的最短距离        初始化顶点未访问
    vector<int> q(nodeCount);        // BFS使用的队列
    dis[0] = 0;
    head = h = t = 0;
    while (t <= h) {
        for (int i = t; i <= h; ++i)
            for (int j = 0; j < nodeCount; ++j) {
                if (linkTable[q[i]][j] > 0) {
                    if (j == q[i]) continue;  // 排除自环
                    if (dis[j] != -1 && (dis[q[i]] - dis[j]) % 2 == 0)
                        return false;         // 说明顶点q[i]和顶点j连接会有奇环产生，不是二部图
                    else if (dis[j] == -1) {  // j没有访问过，入队
                        q[++head] = j;
                        dis[j] = dis[q[i]] + 1;
                    }
                }
            }
        t = h + 1;
        h = head;
    }
    return true;
}
MyGraph::MyGraph(int count) : nodeCount(count) {
    colors.resize(nodeCount);
    make_two_dimension_vector(nodeCount, nodeCount, -1, linkTable);
    nextNodeId = 0;
}
void MyGraph::set_edge(int v, int w) {
    linkTable[v][w] = 1;
    linkTable[w][v] = 1;
}
void MyGraph::set_edge(string a, string b) {
    int n1, n2;
    if (allStrings.find(a) == allStrings.end()) {
        n1 = nextNodeId++;
        allStrings.insert(a);
        string2nodeId.insert(pair<string, int>(a, n1));
    } else {
        n1 = string2nodeId[a];
    }
    if (allStrings.find(b) == allStrings.end()) {
        n2 = nextNodeId++;
        allStrings.insert(b);
        string2nodeId.insert(pair<string, int>(b, n2));
    } else {
        n2 = string2nodeId[b];
    }
    linkTable[n1][n2] = 1;
    linkTable[n2][n1] = 1;
}
void MyGraph::coloring() {
    int colorNum = 2;
    bool found = false;
    while (1) {
        fill(colors.begin(), colors.end(), 0);  //每个节点的颜色都初始化为第一种
        do {
            cout << colors << endl;
            if (!check_if_same_color_adjacent()) {
                found = true;
                break;
            }
        } while (generate_all_k_choices(colors, nodeCount, colorNum));
        if (found) break;
        ++colorNum;
    }
    cout << "need color : " << colorNum << endl;
    cout << "color result : " << colors << endl;
}
bool MyGraph::check_if_same_color_adjacent() {
    for (int i = 0; i < nodeCount; ++i) {
        for (int j = i + 1; j < nodeCount; ++j) {                 //上三角
            if (linkTable[i][j] > 0 && colors[i] == colors[j]) {  //节点相连并且颜色相同
                return true;
            }
        }
    }
    return false;
}
