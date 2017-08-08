#include <iostream>
#include <vector>

using namespace std;

/**
 * 最大子序列和, 输入一组整数, 求出这组数字子序列和中最大值
 * 序列：-2 11 -4 13 -5 -2, 则最大子序列和为20
 * 序列：-6 2 4 -7 5 3 2 -1 6 -9 10 -2, 则最大子序列和为16
 * 线性的算法 O(N)
 */
int calculateMaxSum(vector<int> a, int& start, int& end);

int calculateMaxMultiply(vector<int> a, int& start, int& end);
