#include "utilities.h"
using namespace std;


//生成全排列，生成k->n的全排列
void all_permutation(vector<int> &a, int k, int n){
    if (k == n-1)    {        //终止条件，打印该序列
        cout<<a<<endl;
    }
    else {
        for (int i = k; i < n ; i++) {
            swap(a, k, i);
            all_permutation(a, k + 1, n);
            swap(a, k, i);
        }
    }
}
//生成C(n,k)的组合，按照字典序
bool next_combination(vector<int> &comb, int k, int n){
    int change_bit = k - 1;
    int max_value = n;
    while(change_bit>=0 && comb[change_bit] >= max_value){
        max_value--;                    //前一位的最大值少一位
        change_bit --;
    }
//    cout<<change_bit<<endl;
    if(change_bit < 0)   return false;   //最后一个组合
    else{
        int current_value = comb[change_bit] + 1;
        while(change_bit < k){
            comb[change_bit] = current_value;
            change_bit++;
            current_value++;
        }
    }
    return true;
}


void test_permutation(){
    int n = 4;
    vector<int> a = getIncrementalVector(n);
    all_permutation(a, 0, n);

    cout<<"test next_permutation: "<<endl;
    vector<int> b = getIncrementalVector(n);
    do{
        cout<<b<<endl;
    }
    while (next_permutation(b.begin(), b.begin() + 4));


    cout<<"combination  :"<<endl;
    vector<int> c = getIncrementalVector(n);
    do{
        cout<<c<<endl;
    }
    while (next_combination(c, 4, 6));

//    for(int j = 0; j<7 ; j++){
//        for (int i = 0; i<n ; i++)  {cout<<c[i]<<" ";}
//        cout<<endl;
//        NextComb(c,4,5);
//    }

}
