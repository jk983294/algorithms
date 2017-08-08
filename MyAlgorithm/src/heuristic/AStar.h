#ifndef ASTAR_H
#define ASTAR_H

#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

/**
 * f(n) = g(n) + h(n)  评估函数=已经耗费的 + 估计还要再耗费的
 * 水平竖直移动代价为10，斜着移动代价为14
 * 清除上一次寻路的脏数据，为下一次的寻路准备:
 * refreshData: 只需要清理open表和closed表(也就是whichList),f,g,h,father的脏数据不会影响下一次寻路
 * 优化方法是: 二叉堆中顺序遍历找到需要改变的节点，然后修改他的f,然后向上调整，跟双亲比较以上移
 */

const int dirs[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};  // 8个移动方向
const int MaxN = 999;

class position {
    friend ostream &operator<<(ostream &os, const position &a);

public:
    position(int a, int b) : x(a), y(b) {}
    position() {}
    bool operator>(const position &b) const { return this->f > b.f; }    // 最小优先
    bool operator<(const position &b) const { return this->f < b.f; }    // 最大优先
    bool operator<=(const position &b) const { return this->f <= b.f; }  // 最大优先
    int x{0}, y{0};
    int f{0};  // 代价函数
};
ostream &operator<<(ostream &os, const position &a) {
    os << a.x << "_" << a.y << "_" << a.f;
    return os;
}
class BiMinHeap {  // 最小二叉堆
public:
    BiMinHeap() { size = 0; }  // 0号元素完全二叉树不用
    void clear() { size = 0; };
    bool empty() { return size == 0; };
    int findItem(position &p) {  // 返回p在heap中的位置下标
        for (int i = 1; i <= size; i++) {
            if ((p.x == heap[i].x) && (p.y == heap[i].y)) return i;
        }
        return -1;
    };
    void maintainHeap(int index) {  // heap[index]修改过，需要维护heap结构
        position tmp;
        while (index > 1) {
            if (heap[index] < heap[index / 2]) {  // 自己比父亲小，需要上移
                tmp = heap[index];
                heap[index] = heap[index / 2];
                heap[index / 2] = tmp;
                index /= 2;
            } else
                break;
        }
    }
    bool changeItem(position &p) {
        int index = findItem(p);
        if (index > 0) {
            heap[index] = p;
            maintainHeap(index);
            return true;
        } else
            return false;
    }
    void push(position item) {
        size++;
        int pos = size;
        while (pos > 1) {
            if (item < heap[pos / 2]) {
                heap[pos] = heap[pos / 2];
                pos /= 2;
            } else
                break;
        }
        heap[pos] = item;
    };
    void pop() {
        if (size > 0) {
            position k = heap[size--];  // get last element
            int pos = 1, child = 2;     // 左子女
            while (child <= size) {
                if (child < size) {                              // 两个子女
                    if (heap[child] > heap[child + 1]) child++;  // child为较小的子女
                }
                if (k <= heap[child])
                    break;  // find k's place
                else {
                    heap[pos] = heap[child];  // 较小子女向上移
                    pos = child;
                    child *= 2;
                }
            }
            heap[pos] = k;
        }
    };
    position &top() { return heap[1]; };
    void print() {
        for (int i = 1; i <= size; i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    };

public:
    int size;  // size = heap.size() -1  0号元素完全二叉树不用
    position heap[MaxN];
};

class AStar {
public:
    AStar(string mapPath);
    void readMap(string mapPath);
    vector<pair<int, int>> findPath(position &startPoint, position &endPoint);
    void print();
    int f_cost(position &pos);                      // 起点到终点的代价  f = g + h
    int g_cost(position &now, position &nextStep);  // 起点到当前节点的代价
    int h_cost(position &pos);                      // 当前节点到终点的启发式代价
    bool isWalkable(const position &pos);
    void pushIntoOpenList(position &pos);
    void setFather(position &now, position &nextstep);
    void refreshData();  // 清除上一次寻路的脏数据，为下一次的寻路准备
public:
    position start, end;
    int height, width;
    int **map;  // -1：block  0: walkable
    int **fatherX, **fatherY;
    int **f, **g, **h;
    BiMinHeap open;
    int **whichList;  // (x,y)在哪个list 0: 无 1: 节点在开启列表 2: 节点在关闭列表
};
vector<pair<int, int>> AStar::findPath(position &startPoint, position &endPoint) {
    refreshData();

    start = startPoint;
    end = endPoint;

    g[start.x][start.y] = 0;
    h[start.x][start.y] = h_cost(start);
    f[start.x][start.y] = g[start.x][start.y] + h[start.x][start.y];
    start.f = f[start.x][start.y];  // g+h
    setFather(start, start);
    pushIntoOpenList(start);

    position now, next;
    while (!open.empty()) {
        now = open.top();
        open.pop();
        whichList[now.x][now.y] = 2;              // push into closed list
        if (whichList[end.x][end.y] == 2) break;  // find path

        for (int i = 0; i < 8; i++) {  // 8个方向
            next.x = now.x + dirs[i][0];
            next.y = now.y + dirs[i][1];
            if ((!isWalkable(next)) || (whichList[next.x][next.y] == 2)) {  // 下一个节点不通或者已经处理过
                continue;
            } else if (whichList[next.x][next.y] == 1) {  // 节点在open list中，应该看是否更新在open list中的g_cost
                if (g[next.x][next.y] > g_cost(now, next)) {  // 新的路径有更好的g
                    // cout << "new good path: from " << now << " to " << next << endl;
                    setFather(now, next);
                    g[next.x][next.y] = g_cost(now, next);
                    f[next.x][next.y] = g[next.x][next.y] + h[next.x][next.y];
                    next.f = f[next.x][next.y];  // g+h
                    // 维护open list
                    open.changeItem(next);
                }
            } else {
                g[next.x][next.y] = g_cost(now, next);
                h[next.x][next.y] = h_cost(next);
                f[next.x][next.y] = g[next.x][next.y] + h[next.x][next.y];
                next.f = f[next.x][next.y];  // g+h
                setFather(now, next);
                pushIntoOpenList(next);
            }
        }
    }

    // print path 根据fatherX, fatherY回退到起点
    vector<pair<int, int>> result;
    now = end;
    while (1) {
        next.x = fatherX[now.x][now.y];
        next.y = fatherY[now.x][now.y];
        if ((now.x != start.x) || (now.y != start.y)) {
            result.push_back({now.x, now.y});
            now = next;
        } else
            break;
    }
    result.push_back({start.x, start.y});
    return result;
}
void AStar::refreshData() {
    open.clear();
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) whichList[i][j] = 0;
}
void AStar::pushIntoOpenList(position &pos) {
    open.push(pos);
    whichList[pos.x][pos.y] = 1;
}
bool AStar::isWalkable(const position &pos) {
    if (map[pos.x][pos.y] < 0)
        return false;
    else
        return true;
}
void AStar::setFather(position &now, position &nextStep) {
    fatherX[nextStep.x][nextStep.y] = now.x;
    fatherY[nextStep.x][nextStep.y] = now.y;
}
int AStar::g_cost(position &now, position &nextStep) {
    if ((fabs(now.x - nextStep.x) + fabs(now.y - nextStep.y)) > 1)
        return g[now.x][now.y] + 14;
    else
        return g[now.x][now.y] + 10;
}
int AStar::h_cost(position &pos) {  // manhattan distance * 10
    return (fabs(pos.x - end.x) + fabs(pos.y - end.y)) * 10;
}
void AStar::print() {
    cout << "map: " << endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cout << map[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "which list: " << endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cout << whichList[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "father: " << endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cout << fatherX[i][j] << "_" << fatherY[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "f g h: " << endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cout << g[i][j] << "_" << h[i][j] << "_" << f[i][j] << "\t";
        }
        cout << endl;
    }
}
AStar::AStar(string mapPath) { readMap(mapPath); }
void AStar::readMap(string mapPath) {
    ifstream ifs(mapPath.c_str());
    ifs >> height >> width;
    whichList = new int *[height];
    map = new int *[height];
    fatherX = new int *[height];
    fatherY = new int *[height];
    f = new int *[height];
    g = new int *[height];
    h = new int *[height];
    for (int i = 0; i < height; i++) {
        map[i] = new int[width];
        fatherX[i] = new int[width];
        fatherY[i] = new int[width];
        whichList[i] = new int[width];
        f[i] = new int[width];
        g[i] = new int[width];
        h[i] = new int[width];
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            ifs >> map[i][j];
            whichList[i][j] = 0;
            fatherX[i][j] = -1;
            fatherY[i][j] = -1;
            f[i][j] = -1;
            g[i][j] = -1;
            h[i][j] = -1;
        }
    }
}

#endif
