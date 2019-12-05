#ifndef MYUTILITY_H
#define MYUTILITY_H

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

const int NEGA_BIG_INT = 0x80000001;  //最大负整数，补码表示
const int POS_BIG_INT = 0x7fffffff;

// make_two_dimension_vector(Type *array, int len, vector<Type>& v) // 创建二维vector数组
// vector<Type> to_vector(Type *array, int len)                    // 一维指针数组转为vector
// bool generate_all_k_choices(vector<int>& choice, int n, int k); // 每个决策有k的选择，有n个决策的所有组合 k^n
// int count_sorted_array_range(vector<int> a, int startNum, int endNum);  // [startNum, endNum]之间的数有多少个

inline int count_sorted_array_range(vector<int> a, int startNum, int endNum) {
    int cnt = 0;
    vector<int>::iterator lowIter = upper_bound(a.begin(), a.end(), startNum);
    vector<int>::iterator upIter = upper_bound(a.begin(), a.end(), endNum);
    if (upIter == a.begin() || lowIter == a.end()) return 0;
    if (lowIter != a.begin()) {
        --lowIter;
        if (*lowIter < startNum) ++lowIter;
    }
    if (upIter != a.end() && (*upIter > startNum)) --upIter;
    cnt = upIter - lowIter + 1;
    if (upIter == a.end()) --cnt;
    return cnt;
}

inline bool generate_all_k_choices(vector<int>& choice, int n, int k) {
    for (int i = n - 1; i >= 0; --i) {
        if (choice[i] != k - 1) {  // find first pos not equal k-1, add 1 and then set backward all 0
            ++choice[i];
            fill(choice.begin() + i + 1, choice.end(), 0);
            return true;
        }
    }
    return false;  // 遍历完毕，没有决策了
}

// 记录原次序的快排
inline void quick_sort_with_original_order(vector<int>& a, vector<int>& index1, int left, int right) {
    if (left < right) {
        int pivot = a[left], tmp, tmpIndex;
        int i = left, j = right + 1;
        do {
            do
                ++i;
            while (i <= right && a[i] < pivot);  //防止右越界
            do
                --j;
            while (a[j] > pivot);
            if (i < j) {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
                tmpIndex = index1[i];
                index1[i] = index1[j];
                index1[j] = tmpIndex;
            }
        } while (i < j);
        tmp = a[j];
        a[j] = pivot;
        a[left] = tmp;
        tmpIndex = index1[j];
        index1[j] = index1[left];
        index1[left] = tmpIndex;
        quick_sort_with_original_order(a, index1, left, j - 1);
        quick_sort_with_original_order(a, index1, j + 1, right);
    }
}

template <typename Type>
void reverse_vector(vector<Type>& v, int begin, int end) {
    int step = (begin + end) / 2 - begin;
    Type tmp;
    for (int i = 0; i <= step; ++i) {
        tmp = v[begin + i];
        v[begin + i] = v[end - i];
        v[end - i] = tmp;
    }
}

template <typename Type>
void make_two_dimension_vector(size_t dimension1, size_t dimension2, Type initValue, vector<vector<Type> >& v) {
    v.resize(dimension1);
    for (size_t i = 0; i < dimension1; ++i) v[i].resize(dimension2, initValue);
}

template <typename Type>
void to_vector(Type* array, int len, vector<Type>& v) {
    vector<Type> tmp(array, array + len);
    v.swap(tmp);
}
template <typename Type>
vector<Type> to_vector(Type* array, int len) {
    vector<Type> tmp(array, array + len);
    return tmp;
}
template <typename Type>
inline std::ostream& operator<<(std::ostream& os, const vector<Type>& v) {
    size_t size = v.size();
    if (size > 0) {
        for (size_t i = 0; i < size - 1; i++) os << v[i] << " ";
        os << v[size - 1];
    }
    return (os);
}
template <typename Type>
inline std::ostream& operator<<(std::ostream& os, const vector<vector<Type> >& v) {
    for (unsigned int i = 0; i < v.size(); i++) os << i << ":\t\t" << v[i] << std::endl;
    return (os);
}

#endif
