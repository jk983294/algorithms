#include <iostream>
#include <set>
#include <vector>
#include "utilities.h"

using namespace std;

/**
 * 找到一个数n的加法因子集合, 集合中的所有数加起来 = n, 集合中的数不重复
 */
void divideToSub(vector<set<int>>& v, set<int>& s, int n, int moreThan) {
    int half = n / 2;
    int j;
    for (int i = moreThan + 1; i <= half; i++) {
        j = n - i;
        if (j < moreThan)
            continue;
        else if (i == j)
            continue;
        else if ((s.find(i) != s.end()) || (s.find(j) != s.end()))
            continue;
        else {
            s.insert(i);

            set<int> tmp(s);
            tmp.insert(j);
            v.push_back(tmp);

            divideToSub(v, s, j, i);
            s.erase(i);
        }
    }
}

vector<set<int>> divideToSub(int n) {
    vector<set<int>> v;
    set<int> s;
    divideToSub(v, s, n, 0);
    return v;
}
