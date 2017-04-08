#include "utilities.h"
using namespace std;

class LCS {
public:
    vector<vector<int> > lcs;
    string x;
    string y;
    set<string> results;
public:
    void lcs_length();                              //找到lcs的最长序列长，结果保存在lcs矩阵中
    void find_all_lcs();
    void find_all_lcs(int i, int j, string str);    //根据lcs矩阵，打印所有lcs，每个点每次最多能压栈3次,omega(3^n)，路径x条，O(x*n)
};
//最长公共子序列的长度
void LCS::lcs_length(){
    int n= x.size();
    int m = y.size();
    getMatrix(lcs, n + 1, m + 1, 0);
    int i, j;

    for(i=0; i <= n; i++) lcs[i][0] = 0;
    for(j=0; j <= m; j++) lcs[0][j] = 0;

    for(i=1;i <= n; i++){
        for(j=1; j <= m; j++){
            if(x[i - 1] == y[j - 1]) {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            } else {
                lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
            }
        }
    }

    cout<<lcs<<endl;
    cout<<"LCS_length : "<<lcs[n][m]<<endl;
}
void LCS::find_all_lcs(){
    find_all_lcs(x.size(), y.size(), "");
    cout<<results<<endl;
}
void LCS::find_all_lcs(int i, int j, string str){
    if(i == 0 || j == 0){
        reverse(str.begin(), str.end());
        results.insert(str);
        return;
    }
    if(lcs[i][j] == lcs[i - 1][j]) find_all_lcs(i - 1, j, str);
    if(lcs[i][j] == lcs[i][j - 1]) find_all_lcs(i, j - 1, str);
    if(lcs[i][j] == lcs[i - 1][j - 1] + 1 && x[i - 1] == y[j - 1]) find_all_lcs(i - 1, j - 1, str + x[i - 1]);
}
void test_LCS(){
    //金远平书例子
//    string x("abdebcbb");
//    string y("adacbcb");

    //算法导论例子
    LCS lcs;
    lcs.x="abcbdab";
    lcs.y="bdcaba";
    lcs.lcs_length();
    lcs.find_all_lcs();
}
