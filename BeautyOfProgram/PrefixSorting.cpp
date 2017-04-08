#include "PrefixSorting.h"

void test_PrefixSort(){
    int array[] = {0,7,8,9,4,5,6,1,2,3};
    PrefixSort ps(array, sizeof(array) / sizeof(int));
    ps.upbound();                                       //找到上界
    ps.search_least_time(ps.array,0);
    cout<<ps.totaltimes<<endl<<ps.upbound_times<<endl<<ps.upindex<<endl;
}
bool PrefixSort::has_sorted(vector<int> &a){
    for(unsigned int i = 0; i< a.size()-1; ++i){
        if(a[i]<a[i+1])
        return false;
    }
    return true;
}
int PrefixSort::search_least_time(vector<int> a, int cnt){
    if (has_sorted(a)){
        if (cnt < upbound_times)
            upbound_times = cnt;
        return cnt;
    }
    if(cnt >= upbound_times-1)    return upbound_times + 1;

    int min_times = 0x7fffffff, times, updownindex;
    for (int i = 0; i < size -1; ++i)    {
        reverse(a.begin()+i,a.end());
        ++totaltimes;
        times = search_least_time(a,cnt+1);
        if(times < min_times){
            min_times = times;
            updownindex = i;
        }
        if (times == upbound_times ){
            upindex[cnt] = updownindex;
        }
        reverse(a.begin()+i,a.end());
    }
    return min_times;
}
//找到最大值，然后翻转，最多2(n-1)次，求得上界
void PrefixSort::upbound(){
    vector<int> a;    a = array;    vector<int>::iterator itr,base;
    upbound_times = 0;    base = a.begin();
    for (int i = 0; i < size; ++i)    {
        itr = max_element(base , a.end());
        if (itr != base ){
            if (itr != a.end()-1){
                reverse(itr,a.end());
                upbound_times++;
            }
            reverse(base,a.end());
            upbound_times++;
        }
        base++;
    }
    upindex.resize(upbound_times);
    cout<<"upbound_times : "<<upbound_times<<endl;
}
PrefixSort::PrefixSort(int *a, int len){
    array.resize(len);
    size = len;
    totaltimes = 0;
    copy(a,a+len,array.begin());
    cout<<array<<endl;
}
