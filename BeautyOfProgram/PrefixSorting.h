#ifndef PREFIXSORTING_H
#define PREFIXSORTING_H

#include "myutility.h"

class PrefixSort
{
public:
    vector<int> array, upindex;             //数组，记录第N次的翻转位置
    int size, upbound_times, totaltimes;    //数组大小，翻转次数上界，找到最优解总共翻转次数
public:
    PrefixSort(int *a, int len);
    void upbound();                         //找到最大值，然后翻转，最多2(n-1)次，求得上界
    int search_least_time(vector<int> a, int cnt);
    bool has_sorted(vector<int> &a);
};

void test_PrefixSort();


#endif
