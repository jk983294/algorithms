#include "myutility.h"


int count_sorted_array_range(vector<int> a, int startnum, int endnum){
    int cnt = 0;
    vector<int>::iterator lowiter = upper_bound(a.begin(),a.end(),startnum);
    vector<int>::iterator upiter = upper_bound(a.begin(),a.end(),endnum);
    if(upiter == a.begin() || lowiter == a.end()) return 0;
    if (lowiter != a.begin()  ){
        --lowiter;
        if(*lowiter < startnum)
            ++lowiter;
    }
    if (upiter != a.end() && (*upiter > startnum ) )
        --upiter;
    cnt = upiter - lowiter + 1;
    if (upiter == a.end())  --cnt;
    return cnt;
}
bool generate_all_k_choices(vector<int> &choice,int n, int k){
    for (int i = n-1; i >= 0; --i ){
        if(choice[i] != k-1){       //find first pos not equal k-1, add 1 and then set backward all 0
            ++choice[i];
            fill(choice.begin()+i+1,choice.end(), 0);
            return true;
        }
    }
    return false;                   //遍历完毕，没有决策了
}
//生成从0 ... N-1的序列
void make_vector_index(vector<int> &index, int count){
    index.resize(count);
    for (int i = 0; i < count; ++i)    index[i] = i;
}
//记录原次序的快排
void quicksort(vector<int> &a, vector<int> &index1, int left, int right){
    if(left < right){
        int povit = a[left], tmp,tmpindex;
        int i = left, j = right+1;
        do {
            do ++i; while ( i <= right && a[i] < povit );    //防止右越界
            do --j; while (a[j] > povit );
            if( i < j ){
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
                tmpindex = index1[i];
                index1[i] = index1[j];
                index1[j] = tmpindex;
            }
        } while (i < j);
        tmp = a[j];
        a[j] = povit;
        a[left] = tmp;
        tmpindex = index1[j];
        index1[j] = index1[left];
        index1[left] = tmpindex;
        quicksort(a,index1,left, j-1);
        quicksort(a,index1,j+1, right);
    }
}
