/*
最大子序列和
输入一组整数，求出这组数字子序列和中最大值。也就是只要求出最大子序列的和。例如：
序列：-2 11 -4 13 -5 -2，则最大子序列和为20。
序列：-6 2 4 -7 5 3 2 -1 6 -9 10 -2，则最大子序列和为16。
//线性的算法O(N)
**/



#include <iostream>
using namespace std;

//线性的算法O(N)
void calculateMaxSum(int *a,int size){
    int max = -99999, thisMax = 0;
    int beginPos = -1, endPos = 0;
    for(int i=0; i < size; i++){
        thisMax += a[i];
        if(thisMax > max)  {
            max = thisMax;
            endPos = i;
        }
        if(thisMax < 0) {
            thisMax = 0;
            beginPos = i;
        }
    }
    cout<<max<<endl;
    cout<<"from "<<beginPos + 1<<" to "<<endPos<<endl;
}

void calculateMaxMultiply(int *a,int size){
    int max = 1, positiveMax = 0, negativeMax = 0;
    int beginPos = -1, positiveEndPos = 0, negativeEndPos = 0;
    for(int i=0; i < size; i++){
        max *= a[i];
        if(max > 0 && positiveMax < max)  {
            positiveMax = max;
            positiveEndPos = i;
        }
        if(max < 0 && negativeMax < max)  {
            negativeMax = max;
            negativeEndPos = i;
        }
        if(max == 0) {
            max = 1;
            beginPos = i;
        }
    }
    cout<<positiveMax<<endl;
    cout<<"from "<<beginPos + 1<<" to "<<positiveEndPos<<endl;
}

void testMaxSumSubVector(){
    cout<<"testMaxSumSubVector begin."<<endl;
    // one test case : -2, 11, -4, 13, -5, -2
    // another test case : -6, 2, 4, -7, 5, 3, 2, -1, 6, -9, 10, -2
    int a[] = {-6, 2, 4, -7, 5, 0, 2, -1, 6, -9, 10, -2};   //
    int size = sizeof(a)/sizeof(int);
    calculateMaxSum(a,size);
    calculateMaxMultiply(a,size);
    cout<<"testMaxSumSubVector end."<<endl;
}