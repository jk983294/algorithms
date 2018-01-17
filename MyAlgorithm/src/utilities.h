#ifndef MY_ALGORITHM_UTILITIES_H
#define MY_ALGORITHM_UTILITIES_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

vector<int> getIncrementalVector(int n);

template <typename Type>
vector<vector<Type> >& getMatrix(vector<vector<Type> >& matrix, int rowSize, int columnSize, Type initValue) {
    matrix.resize(rowSize);
    for (int k = 0; k < rowSize; ++k) {
        matrix[k].resize(columnSize, initValue);
    }
    return matrix;
}

template <typename Type>
void swap(vector<Type>& a, int i, int j) {
    Type tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

template <typename Type>
inline std::ostream& operator<<(std::ostream& os, const set<Type>& _set) {
    for (auto itr = _set.begin(); itr != _set.end(); itr++) os << *itr << " ";
    return os;
}

template <typename Type>
inline std::ostream& operator<<(std::ostream& os, const vector<Type>& v) {
    for (auto itr = v.begin(); itr != v.end(); itr++) os << *itr << " ";
    return os;
}
template <typename Type>
inline std::ostream& operator<<(std::ostream& os, const vector<vector<Type> >& v) {
    for (auto itr = v.begin(); itr != v.end(); itr++) os << *itr << endl;
    return os;
}

#endif
