#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

static const int maxlen = 100;
static const int MAXNUM = 999999;

class EggDropPuzzle {
public:
    /**
     * Minimum number of trials in worst case with eggCount eggs and height floors is cost[eggCount][height]
     */
    int cost[maxlen][maxlen];
    int opt[maxlen][maxlen];  // 记录断开位置
    int eggcount;             // 鸡蛋数
    int height;               // 楼高
public:
    void calculate_cost();
    void print_cost();
};
void EggDropPuzzle::calculate_cost() {
    int i, j, k, costMin, currentMin, MinIndex;
    for (i = 0; i <= eggcount; i++) {
        cost[i][0] = 0;
        opt[i][0] = -1;
    }
    for (j = 0; j <= height; j++) {
        cost[0][j] = 0;
        cost[1][j] = j;
        opt[0][j] = -1;
        opt[1][j] = -1;
    }  // 1个鸡蛋去试j层楼要j次

    for (i = 2; i <= eggcount; i++) {
        for (j = 1; j <= height; j++) {
            costMin = MAXNUM;
            MinIndex = -1;
            for (k = 1; k <= j; k++) {
                currentMin = max(cost[i - 1][k - 1], cost[i][j - k]);
                if (costMin > currentMin) {
                    costMin = currentMin;
                    MinIndex = k;  // 记录第几层断开
                }
            }
            cost[i][j] = 1 + costMin;
            opt[i][j] = MinIndex;
        }
    }
}
void EggDropPuzzle::print_cost() {
    cout << "cost matrix : " << endl;
    for (int i = 0; i <= eggcount; i++) {
        for (int j = 0; j <= height; j++) {
            cout << cost[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << "opt matrix : " << endl;
    for (int i = 0; i <= eggcount; i++) {
        for (int j = 0; j <= height; j++) {
            cout << opt[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
