#ifndef MYALGORITHM_UTILITIES_H
#define MYALGORITHM_UTILITIES_H

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <utility>
#include "VisualAssist.h"
using namespace std;


template<typename Type>
vector<vector<Type> >& getMatrix(vector<vector<Type> >& matrix, int rowSize, int columnSize, Type initValue) {
    matrix.resize(rowSize);
    for (int k = 0; k < rowSize; ++k) {
        matrix[k].resize(columnSize, initValue);
    }
    return matrix;
}

template<typename Type>
void swap(vector<Type>& a, int i, int j) {
    Type tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

vector<int> getIncrementalVector(int n) {
    vector<int> a(n);
    for (int i = 0; i<n ; i++) {
        a[i] = i;
    }
    return a;
}

#endif //MYALGORITHM_UTILITIES_H
