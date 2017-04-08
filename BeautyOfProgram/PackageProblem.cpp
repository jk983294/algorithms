#include "PackageProblem.h"

void test_b_o_p_1_6(){
    cout<<"\ntest_b_o_p_1_6 "<<endl;
    int w[] = {1,2,8,4,16};
    int p[] = {3,4,2,5,2};
    int m[] = {50,20,30,50,20};                                                 //物品个数
    int totalWeight = 100;
    Sack s(w,p,m, sizeof(w)/sizeof(int), totalWeight);
    s.muilti_sack();
}
void test_Sack(){
    test_b_o_p_1_6();

    int w[] = {3,4,5};
    int p[] = {4,5,6};
    int m[] = {1,1,1};                                                          //物品个数
    int totalWeight = 10;
    Sack s(w,p,m, sizeof(w)/sizeof(int), totalWeight);
    s.zero_one_sack_basic();
    s.zero_one_sack_space_opt();
    s.muilti_sack();
}
void Sack::muilti_sack(){
    vector<int> f;                                                              //一维数组充当二维，因为当前维的计算只与上一维有关
    initvalue = 0;
    f.resize(totalWeight+1,initvalue);
    cout<<f<<endl;
    int notpackvalue = 0, packvalue = 0;                                        //记录i件物品不装入和装入时的总价值
    for (int i = 1; i <= M; ++i){
        for (int j = totalWeight; j >= 0; --j){
            vector<int> values(Mi[i] + 1, initvalue);
            for (int k =0; k <= Mi[i]; ++k){
                if( j >= k*weights[i])
                    values[k] = f[ j - k * weights[i] ] + k * prices[i];        //装入k个物品i，则前 i-1 件的总空间变为 j - k*weights[i]
            }
            f[j] = *max_element(values.begin(),values.end());
        }
    }
    cout<<f<<endl;
    cout<<"最大价值为 ： "<<f[totalWeight]<<endl;
}
void Sack::zero_one_sack_basic(){
    vector<vector<int> > f;
    initvalue = 0;
    make_two_demision_vector(M+1, totalWeight+1, initvalue , f);
    int notpackvalue = 0, packvalue = 0;                                //记录i件物品不装入和装入时的总价值
    for (int i = 1; i <= M; ++i){
        for (int j = 1; j <= totalWeight; ++j){
            if( j >= weights[i])
                packvalue = f[i - 1][ j - weights[i] ] + prices[i];     //装入物品i，则前 i-1 件的总空间变为 j - weights[i]
            else packvalue = initvalue;
            notpackvalue = f[ i -1 ][ j ];                              //不装入物品 i 的总价值
            f[i][j] = max(packvalue,notpackvalue);
        }
    }
    cout<<f<<endl;
    cout<<"最大价值为 ： "<<f[M][totalWeight]<<endl;
}
void Sack::zero_one_sack_space_opt(){
    vector<int> f;                                                      //一维数组充当二维，因为当前维的计算只与上一维有关
    initvalue = 0;
    f.resize(totalWeight+1,initvalue);
    cout<<f<<endl;
    int notpackvalue = 0, packvalue = 0;                                //记录i件物品不装入和装入时的总价值
    for (int i = 1; i <= M; ++i){
        for (int j = totalWeight; j >= 0; --j){
            if( j >= weights[i])
                packvalue = f[ j - weights[i] ] + prices[i];            //装入物品i，则前 i-1 件的总空间变为 j - weights[i]
            else packvalue = initvalue;
            notpackvalue = f[ j ];                                      //不装入物品 i 的总价值
            f[j] = max(packvalue,notpackvalue);
        }
    }
    cout<<f<<endl;
    cout<<"最大价值为 ： "<<f[totalWeight]<<endl;
}
Sack::Sack(int *w,int *p, int *m, int len, int totalW){
    to_vector(w,len,weights);    to_vector(p,len,prices);    to_vector(m,len,Mi);
    weights.insert(weights.begin(),0);          //0号位置不用
    prices.insert(prices.begin(),0);            //0号位置不用
    Mi.insert(Mi.begin(),0);                    //0号位置不用
    M = len;    totalWeight=totalW;
    cout<<weights<<endl<<prices<<endl;
}
