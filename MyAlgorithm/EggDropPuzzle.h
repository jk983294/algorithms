#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

const int maxlen = 100;
const int MAXNUM = 999999;

class EggDropPuzzle
{
public:
    int cost[maxlen][maxlen];   //cost[eggcount][heigh]即为所求
    int opt[maxlen][maxlen];    //记录断开位置
    int eggcount;      //鸡蛋数
    int heigh;      //楼高
public:
    void calculate_cost();
    void print_cost();
};
void EggDropPuzzle::calculate_cost(){
    int i,j,k,costMin,currentMin,MinIndex;
    for(i=0;i <= eggcount;i++) {
        cost[i][0] = 0;     opt[i][0] = -1;
    }
    for(j=0;j <= heigh;j++)  {
        cost[0][j] = 0; cost[1][j] = j;
        opt[0][j] =-1; opt[1][j] = -1;
    }    //1个鸡蛋去试j层楼要j次

    for(i=2;i <= eggcount;i++){
        for(j=1;j <= heigh;j++){
            costMin = MAXNUM;    MinIndex = -1;
            for(k = 1; k<= j; k++){
                currentMin = max(cost[i-1][k-1],cost[i][j-k]);
                if(costMin > currentMin){
                    costMin = currentMin;
                    MinIndex = k;       //记录第几层断开
                }
            }
            cost[i][j] = 1+costMin;
            opt[i][j] = MinIndex;
        }
    }
}
void EggDropPuzzle::print_cost(){
    cout<<"cost matrix : "<<endl;
    for(int i=0;i <= eggcount;i++){
        for(int j=0;j <= heigh;j++){
            cout<<cost[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl<<"opt matrix : "<<endl;
    for(int i=0;i <= eggcount;i++){
        for(int j=0;j <= heigh;j++){
            cout<<opt[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void test_EggDropPuzzle(){

    EggDropPuzzle edp;
    edp.eggcount=2;
    edp.heigh=32;
    edp.calculate_cost();
    edp.print_cost();

}
