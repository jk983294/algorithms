#ifndef MYUTILITY_H
#define MYUTILITY_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

const double BIGDOUBLE = 10e10;
const int NEGA_BIG_INT = 0x80000001;                                //最大负整数，补码表示
const int POS_BIG_INT = 0x7fffffff;

//make_two_demision_vector                                          创建二维vector数组
//(Type *array, int len, vector<Type>& v)                           一维指针数组转为vector
//vector<Type> to_vector(Type *array, int len)                      一维指针数组转为vector
bool generate_all_k_choices(vector<int> &choice,int n,int k);       //每个决策有k的选择，有n个决策的所有组合 k^n
void quicksort(vector<int> &a, vector<int> &index, int left, int right);        //记录原次序的快排
void make_vector_index(vector<int> &index, int count);                          //生成从0 ... N-1的序列
int count_sorted_array_range(vector<int> a, int startnum, int endnum);          //排序好的数组中，在 [ startnum, endnum ] 之间的数有多少个



template<typename Type>
void reverse_vector(vector<Type>& v, int begin, int end){
    int step = (begin + end) /2 - begin ;
    Type tmp;
    for(int i =0; i <= step; ++i){
        tmp = v[begin + i];
        v[begin + i] = v[end - i];
        v[end - i] = tmp;
    }
}
template<typename Type>
void make_two_demision_vector(int demision1, int demision2, Type initvalue, vector<vector<Type> >& v){
    v.resize(demision1);
    for(int i =0; i < demision1; ++i)
        v[i].resize(demision2,initvalue);
}

template<typename Type>
void to_vector(Type *array, int len, vector<Type>& v){
    vector<Type> tmp(array,array+len);
    v.swap(tmp);
}
template<typename Type>
vector<Type> to_vector(Type *array, int len){
    vector<Type> tmp(array,array+len);
    return tmp;
}
template<typename Type>
inline std::ostream& operator << (std::ostream& os, const vector<Type>& v)
{
    const unsigned int size = v.size();
    if(size > 0){
        for(unsigned int i = 0; i < size-1; i++)
            os << v[i] << " ";
        os << v[size-1];
    }
    return(os);
}
template<typename Type>
inline std::ostream& operator << (std::ostream& os, const vector< vector<Type> >& v)
{
    for(unsigned int i = 0; i < v.size(); i++)
        os << "Subvector " << i  << "\n"<< v[i] << std::endl;
    return(os);
}

#endif
