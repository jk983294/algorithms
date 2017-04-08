/***
使用动态规划计算矩阵连乘的最佳乘法顺序
***/


#include <iostream>
using namespace std;

const int MaxN = 100;

int m[MaxN][MaxN];      //记录最少乘法数
int s[MaxN][MaxN];          //记录断开位置


int recurrsive_m(int i,int j,int *demensionX, int *demensionY, const int n){
    int min = 999999999;
    int minIndex = 0;
    int multipletimes = 0;
    if(m[i][j] != -1)   return m[i][j];
    else{
        for(int k=i; k< j;k++){
            multipletimes = recurrsive_m(i,k,demensionX,demensionY,n)+recurrsive_m(k+1,j,demensionX,demensionY,n)+demensionX[i]*demensionY[k]*demensionY[j];
            if(multipletimes < min){
                min = multipletimes;    minIndex = k;
            }
        }
        m[i][j] = min;  s[i][j] = minIndex;
        return min;
    }
}


//n个矩阵，每个矩阵的维数放在数组中
void MatrixMultiple(int *demensionX, int *demensionY, const int n){
    for(int i = 0; i< n;i++){
        for(int j = 0; j < n;j++){
            m[i][j] = -1;   s[i][j] = -1;
        }
    }
    for(int i = 0; i< n;i++)    m[i][i] = 0;
    recurrsive_m(0,n-1,demensionX,demensionY,n);
    cout<<m[0][n-1]<<endl;
    for(int i = 0; i< n;i++){
        for(int j = 0; j < n;j++){
            cout<<m[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl<<"path:  "<<endl;
    for(int i = 0; i< n;i++){
        for(int j = 0; j < n;j++){
            cout<<s[i][j]<<" ";
        }
        cout<<endl;
    }
}


void test_MatrixMultiple(){
    int n = 6;
    int demensionX[] = { 30,  35,  15,  5,  10, 20};
    int demensionY[] = { 35,  15,  5,  10,  20, 25};

    MatrixMultiple(demensionX,demensionY,n);
}
